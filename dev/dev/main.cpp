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

#include <rp_logger.hpp>
#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"

#include "hw_config.h"

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

void onClicked(Event<MouseEventType> &event, Clickable* sender)
{
    auto btn = (ui::Button*) sender;
    if (event.Type() == MouseEventType::Clicked)
    {
        printf("Clicked Event function called");
    }
    if(btn){
        btn->color = Color::DarkRed;
    }
    event.SetHandled();
}

int main()
{
    board_init();
    tusb_init();

    printf("\r\nRP DEV\r\n");
    sleep_ms(2000);

    SetupRP();

    // Logger
/*
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr)
        panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    FIL fil;
    const char *const filename = "log.txt";
    fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr)
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    if (f_printf(&fil, "Hello, world!\n") < 0)
    {
        printf("f_printf failed\n");
    }

    rplog::Logger logger;
    logger.AddLoggingFile(&fil, rplog::Level::TRACE);
    logger.Log("TEEST");

    fr = f_close(&fil);
    if (FR_OK != fr)
    {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }
    fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE | FA_READ);
    if (FR_OK != fr && FR_EXIST != fr)
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);

    char buf[256];
    while (f_gets(buf, sizeof buf, &fil))
    {
        printf("%s", buf);
    }

    fr = f_close(&fil);
    if (FR_OK != fr)
    {
        printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    }

    f_unmount(pSD->pcName);
*/
    // GUI

    auto lay = layout::StackLayout(type::Point{60, 10}, type::Width{120}, type::Height{200});
    auto rect1 = ui::Rectangle(type::Width{20}, type::Height{20}, colors::Color::Green);
    rect1.margin = Margin{5, 5, 5, 5};

    lay.AddElement(new ui::Rectangle(type::Width{20}, type::Height{40}, colors::Color::Red));
    lay.AddElement(new ui::Rectangle(type::Width{20}, type::Height{40}, colors::Color::Blue));

    auto btn = new ui::Button{type::Width{30}, type::Height{30}, colors::Color::SemiCyan};

    btn->SetOnClickHandler(MouseEventType::Clicked, onClicked);
    btn->SetText("Button");
    lay.AddElement(btn);


    auto lay1 = layout::StackLayout(type::Point{240, 10}, type::Width{40}, type::Height{1});
    lay1.AddElement(new ui::CheckBox(Width(20),Height(20),Color::Gray,Color::White));
    lay1.AddElement(new ui::Label("Test"));

    auto page = new page::Page();
    page->AddLayout(lay);
    page->AddLayout(lay1);

    extern HID::MOUSE_t MOUSE;
    MOUSE.clicked = true;

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
