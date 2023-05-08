#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/float.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include "bsp/board.h"
#include "tusb.h"

#include "rpgui.hpp"

#include <rp_logger.hpp>


using namespace rpgui;
using namespace rpgui::event;

void ProcessButtons(bool *buttons);
void PrintTimings();

extern void hid_app_task(void);
void LED_blink_task();
void ProcessButtonClicked();

bool led_state;
bool indicatorState = false;

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

void onClicked(MouseEvent<MouseEventType> &event, Clickable *sender)
{
    auto btn = (ui::Button *)sender;
    if (event.Type() == MouseEventType::Clicked)
    {
        printf("Clicked MouseEvent function called");
    }
    if (btn)
    {
        btn->color = Color::DarkRed;
    }
    event.SetHandled();
}

int main()
{
    board_init();
    tusb_init();

    printf("\r\nRP DEV\r\n");

    SetupRP();

    // Logger

    // GUI

    rpgui::core::MainApp::Init();

    auto lay = new layout::StackLayout(type::Point{10, 10}, type::Width{300}, type::Height{200});
    auto rect1 = ui::Rectangle(type::Width{20}, type::Height{20}, colors::Color::Green);

    auto btn = new ui::Button{type::Width{30}, type::Height{30}, colors::Color::SemiCyan};

    btn->SetOnClickHandler(MouseEventType::Clicked, onClicked);
    btn->SetText("Button");
    lay->AddElement(btn);

    auto lay1 = new layout::StackLayout(type::Point{310, 10}, type::Width{80}, type::Height{1});
    lay1->AddElement(new ui::CheckBox(Width(20), Height(20), false, Color::Gray, Color::White));
    std::string binder = "Databinder";
    lay->AddElement(new ui::Label(binder));
    lay->AddElement(new ui::Label("Implicit"));
    lay1->AddElement(new ui::Stepper<int>(Width{10}, Height{11}, Color::Red, Color::Blue, 2));

    auto radBtn = new ui::RadioButton(Width(60), Height(16), Color::Red);
    radBtn->AddItem("Dog");
    radBtn->AddItem("Cat");
    radBtn->AddItem("Camel");
    lay->AddElement(radBtn);

    lay->AddElement(new ui::Switch(Width(10), Height(20), true));

    lay->AddElement(new ui::ProgressBar(Width(10), Height(20), 40.0));

    auto page = new page::Page();
    page->AddLayout(lay);
    page->AddLayout(lay1);

    core::MainApp::AddPage(page);
    while (1)
    {

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
