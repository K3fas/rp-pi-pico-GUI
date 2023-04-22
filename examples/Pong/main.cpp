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

#include "Timers.hpp"

#include "pong.hpp"

void LED_blink_task();
void ProcessButtons(bool *buttons);
void PrintTimings();

extern void hid_app_task(void);

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
    stdio_init_all();
    tusb_init();

    rpgui::core::init();

    printf("VGA HID Example\r\n");
    sleep_ms(2000);

    SetupRP();

    auto game = Pong::PongGame();
    game.Init();

    auto page = new Page();
    page->AddLayout(game.GetView());
    rpgui::core::MainApp::AddPage(page);

    auto timer = rpgui::util::Timers();
    timer.AddStamp("start");
    timer.AddStamp("game update");
    timer.AddStamp("UI update");

    
    while (1)
    {
        timer.Stamp("start");
        game.Update();
        timer.Stamp("game update");
        rpgui::core::MainApp::Update();
        timer.Stamp("UI update");
        timer.PrintStamps();
        // timers.Print();
    }
}