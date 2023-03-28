#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb_data.hpp"

// comment out to disable performance tracking
//#define TIMERS
#define PRINT_CORE0
#define PRINT_CORE1

struct timers_t
{
    struct core_t
    {
        uint64_t start = 0;
        uint64_t tusb = 0;
        uint64_t mainLoop = 0;
        uint64_t draw = 0;
        uint64_t VSync = 0;
    } core0, core1;

    void Print()
    {
#ifdef TIMERS
        const uint32_t interval_on_ms = 1000 * 1000;
        static uint32_t start_us = 0;

        extern HID::KBD_t KBD;
        extern HID::MOUSE_t MOUSE;

        // Blink every interval ms
        if (time_us_32() - start_us < interval_on_ms)
            return; // not enough time

        start_us += interval_on_ms;

        printf("Timing reports, interval 1s, one frame is 16 ms\n");
#ifdef PRINT_CORE0
        printf("\n>Core 0\n");
        printf("Start time: %lld us\n", core0.start);
        printf("TUSB task: %lld us          %f %% \n", core0.tusb, ((float)core0.tusb / (1 / 0.006)));
        printf("Main loop: %lld us          %f %% \n", core0.mainLoop, ((float)core0.mainLoop / (1 / 0.006)));
        printf("Draw task: %lld us          %f %% \n", core0.draw, ((float)core0.draw / (1 / 0.006)));
        printf("VSync wait: %lld us          %f %% \n", core0.VSync, ((float)core0.VSync / (1 / 0.006)));

#endif
#ifdef PRINT_CORE1
        printf("\n>Core 1\n");
        printf("Start time: %lld us\n", core1.start);
        printf("TUSB task: %lld us          %f %% \n", core1.tusb, ((float)core1.tusb / (1 / 0.006)));
        printf("Main loop: %lld us          %f %% \n", core1.mainLoop, ((float)core1.mainLoop / (1 / 0.006)));
        printf("Draw task: %lld us          %f %% \n", core1.draw, ((float)core1.draw / (1 / 0.006)));
        printf("VSync wait: %lld us          %f %% \n", core1.VSync, ((float)core1.VSync / (1 / 0.006)));

        printf("\nKBD task: %lld us          %f %% \n", KBD.processTime, ((float)KBD.processTime / (1 / 0.006)));
        printf("MOUSE task: %lld us          %f %% \n", MOUSE.processTime, ((float)MOUSE.processTime / (1 / 0.006)));
#endif
        KBD.processTime = 0;
        MOUSE.processTime = 0;
#endif
    }
};
