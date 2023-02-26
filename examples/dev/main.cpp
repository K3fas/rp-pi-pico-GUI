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

#include "rpgui.hpp"

#include "timers.hpp"

using namespace rpgui;

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

    printf("RP DEV\r\n");
    sleep_ms(2000);

    SetupRP();

    auto rect = ui::Rectangle(types::Point{10, 10}, types::Width{20}, types::Height{40}, colors::Color::Yellow);
    rect.color = colors::Color::Red;

    auto lay = layout::StackLayout(types::Point{60, 10}, types::Width{120}, types::Height{200});
    lay.AddElement(new ui::Rectangle(types::Point{10, 10}, types::Width{20}, types::Height{40}, colors::Color::Red));
    lay.AddElement(new ui::Rectangle(types::Point{10, 10}, types::Width{20}, types::Height{20}, colors::Color::Green));
    lay.AddElement(new ui::Rectangle(types::Point{10, 10}, types::Width{20}, types::Height{40}, colors::Color::Blue));

    while (1)
    {

        tuh_task();
        hid_app_task();

        rect.Draw();
        lay.Draw();

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