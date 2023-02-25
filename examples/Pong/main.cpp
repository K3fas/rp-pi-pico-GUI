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

#include "pong.cpp"

#include "RP_GUI.hpp"

#include "timers.hpp"

using namespace IVGA;
using namespace UI;

void LED_blink_task();
void ProcessButtons(bool *buttons);
void PrintTimings();

extern void hid_app_task(void);
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
        stdio_init_all();
        tusb_init();

        printf("VGA HID Example\r\n");
        sleep_ms(2000);

        SetupRP();

        auto game = Pong::PongGame();
        game.Init();

        auto mainView = MainView(UI::UpdateSettings::Core0);
        mainView.SetCurrentView(game.GetView());

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

                game.Update();

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
                // timers.Print();
        }
}