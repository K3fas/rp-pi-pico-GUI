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
using namespace rpgui::event;

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

void onClicked(const Event<MouseEventType> &event)
{
    if (event.Type() == MouseEventType::Clicked)
    {
        printf("Clicked Event function called");
    }
}

int main()
{
    board_init();
    tusb_init();

    printf("RP DEV\r\n");
    sleep_ms(2000);

    SetupRP();

    Dispatcher<MouseEventType> dispatcher;

    auto lay = layout::StackLayout(type::Point{60, 10}, type::Width{120}, type::Height{200});
    auto rect1 = ui::Rectangle(type::Width{20}, type::Height{20}, colors::Color::Green);
    rect1.margin = Margin{5, 5, 5, 5};

    lay.AddElement(ui::Rectangle(type::Width{20}, type::Height{40}, colors::Color::Red));
    lay.AddElement(rect1);
    lay.AddElement(ui::Rectangle(type::Width{20}, type::Height{40}, colors::Color::Blue));

    auto btn = ui::Button{type::Width{30}, type::Height{30}, colors::Color::Red};

    btn.AddHandler(MouseEventType::Clicked, onClicked);
    lay.AddElement(btn);

    MouseEvent clicked(MouseEventType::Clicked, "onClickHandler");
    dispatcher.Post(clicked);

    auto lay1 = layout::StackLayout(type::Point{240, 10}, type::Width{40}, type::Height{1});
    lay1.AddElement(rect1);
    lay1.AddElement(rect1);
    lay1.AddElement(rect1);
    lay1.AddElement(rect1);
    lay1.AddElement(rect1);
    lay1.AddElement(rect1);

    auto page = new page::Page();
    page->AddLayout(lay);
    page->AddLayout(lay1);

    core::MainApp::AddPage(page);
    while (1)
    {
        tuh_task();
        hid_app_task();

        core::MainApp::Update();

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