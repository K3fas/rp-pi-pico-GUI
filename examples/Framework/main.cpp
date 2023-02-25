#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/float.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "bsp/board.h"
#include "tusb.h"
#include "tusb_data.hpp"

#include "IVGA.hpp"
#include "RP_GUI.hpp"

#include "timers.hpp"

#define SPEED_TEST

using namespace UI;
using namespace IVGA;
using namespace VColors;

void ProcessButtons(bool *buttons);
void PrintTimings();

extern void hid_app_task(void);
void LED_blink_task();
void ProcessButtonClicked();

bool led_state;
bool indicatorState = false;
timers_t timers;

void SetupRP()
{

#ifndef PICO_DEFAULT_LED_PIN
#warning regular LED pin not found
#else
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
#endif
}

int main()
{
    board_init();
    tusb_init();

    printf("RP GUI Example\r\n");
    sleep_ms(2000);

    SetupRP();

    auto mainView = MainView(UpdateSettings::Core0);
    auto view = View();

    view.AddElement(new Label{"GUI test", Point{WIDTH / 2, 30}, Color::Red, Color::Blue});
    view.AddElement(new UI::Rectangle{IVGA::Rectangle{Point{20, 20}, Width{60}, Height{20}}, Color::Magenta});
    view.AddElement(new Button{IVGA::Rectangle{Point{20, 60}, Width{60}, Height{20}}, Color::Blue, ProcessButtonClicked});
    view.AddElement(new Label{"Button", Point{20, 60}, Color::Red, Color::Tranparent});

    view.AddElement(new Indicator{Radius{10}, Point{160, 70}, &indicatorState, Color::Blue, Color::Red});
    view.AddElement(new Indicator{Radius{10}, Point{60, 180}, &led_state});

#ifdef SPEED_TEST
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            view.AddElement(new UI::Rectangle{IVGA::Rectangle{Point{i * 2, j}, Width{1}, Height{1}}, Color::Red});
        }
    }
#endif

    mainView.SetCurrentView(view);
    while (1)
    {
#ifdef TIMERS
        timers.core0.start = time_us_64();
#endif
        tuh_task();
        hid_app_task();

#ifdef TIMERS
        timers.core0.tusb = time_us_64() - timers.core0.start;
#endif

#ifdef TIMERS
        timers.core0.mainLoop = time_us_64() - timers.core0.tusb - timers.core0.start;
#endif

        mainView.Update();
#ifdef TIMERS
        timers.core0.draw = time_us_64() - timers.core0.mainLoop - timers.core0.start;
#endif

        Core1Wait();
        WaitVSync();
#ifdef TIMERS
        timers.core0.VSync = time_us_64() - timers.core0.draw - timers.core0.start;
#endif
#ifdef TIMERS
        timers.Print();
#endif

        LED_blink_task();
    }
}

void LED_blink_task()
{
    const uint32_t interval_on_ms = 1000;
    const uint32_t interval_off_ms = 2000;
    static uint32_t start_ms = 0;

    // Blink every interval ms
    if (board_millis() - start_ms < interval_off_ms)
        return; // not enough time

    if (led_state)
    {
        start_ms += interval_off_ms;
    }
    else
    {
        start_ms += interval_on_ms;
    }

    gpio_put(PICO_DEFAULT_LED_PIN, !led_state);
    led_state = 1 - led_state; // toggle
}

void ProcessButtonClicked()
{
    indicatorState = !indicatorState;
}