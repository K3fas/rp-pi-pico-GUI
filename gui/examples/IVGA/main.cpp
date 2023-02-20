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

using namespace IVGA;
using namespace VColors;

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

    printf("IVGA Example\r\n");
    sleep_ms(2000);

    SetupRP();

    while (1)
    {
        IDrawRectangle(Rectangle{Point{10, 30}, Width{10}, Height{20}}, Color::Red);
        IDrawRectangle(Point{30, 30}, Width{20}, Height{30}, Color::Cyan);
        IDrawFrame(Rectangle{Point{60, 30}, Point{80, 30}}, Color::Magenta);
        IDrawPoint(Point{100, 30}, Color::Red);
        IDrawLine(Point{110, 30}, Point{110, 80}, Color::Green);
        IDrawCircle(Point{130, 35}, Radius{10}, Color::MoreBlue);
        IDrawText("IVGA Example", Point{WIDTH / 2, 30}, Color::MoreRed);

        Core1Wait();
        WaitVSync();
    }
}