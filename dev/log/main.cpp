#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/float.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#include <rp_logger.hpp>
#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"

#include <iostream>

void LED_blink_task();

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

    stdio_init_all();
    time_init();

    printf("RP DEV\r\n");
    sleep_ms(2000);

    SetupRP();

    // Logger

    // sd_card_t *pSD = sd_get_by_num(0);
    // FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    // if (FR_OK != fr)
    //     panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    // FIL fil;
    // const char *const filename = "log.txt";
    // fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    // if (FR_OK != fr && FR_EXIST != fr)
    //     panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    // if (f_printf(&fil, "Hello, world!\n") < 0)
    // {
    //     printf("f_printf failed\n");
    // }

    // rplog::Logger logger;
    // logger.AddLoggingFile(&fil, rplog::Level::TRACE);
    // logger.Log("TEEST");

    // fr = f_close(&fil);
    // if (FR_OK != fr)
    // {
    //     printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    // }
    // fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    // if (FR_OK != fr && FR_EXIST != fr)
    //     panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);

    // char buf[256];
    // while (f_gets(buf, sizeof buf, &fil))
    // {
    //     printf("%s", buf);
    // }

    // fr = f_close(&fil);
    // if (FR_OK != fr)
    // {
    //     printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
    // }

    std::cout << " COUT TEST MESSAGE" << std::endl;
    auto logger = new rplog::Logger();
    logger->logLevel = rplog::Level::INFORMATION;
    logger->AddSink(std::cout);
    logger->AddSink(std::cerr);
    logger->Log(" LOGGER COUT TRACE MESSAGE", rplog::Level::TRACE);
    logger->Log(" LOGGER COUT DEBUG MESSAGE", rplog::Level::DEBUG);
    logger->Log(" LOGGER COUT INFORMATION MESSAGE", rplog::Level::INFORMATION);
    logger->Log(" LOGGER COUT WARNING MESSAGE", rplog::Level::WARNING);
    logger->Log(" LOGGER COUT ERROR MESSAGE", rplog::Level::ERROR);
    logger->Log(" LOGGER COUT CRITICAL MESSAGE", rplog::Level::CRITICAL);

    std::cout << std::endl
              << "Static logger test:" << std::endl;
    rplog::Logger::logTrace(std::cout, "LOGGER COUT TRACE MESSAGE");
    rplog::Logger::logDebug(std::cout, "LOGGER COUT DEBUG MESSAGE");
    rplog::Logger::logInfo(std::cout, "LOGGER COUT INFORMATION MESSAGE");
    rplog::Logger::logWarning(std::cout, "LOGGER COUT WARNING MESSAGE");
    rplog::Logger::logError(std::cout, "LOGGER COUT ERROR MESSAGE");
    rplog::Logger::logCritical(std::cout, "LOGGER COUT CRITICAL MESSAGE");

    auto result = logger->AddFile("text.txt");
    result = logger->AddFile("text.txt");
    std::cout << result;
    logger->Log("FILE TEST !!!", rplog::Level::INFORMATION);
    logger->CloseFiles();
    rplog::Logger::DisposeSD();

    // f_unmount(pSD->pcName);
    while (1)
    {
        LED_blink_task();
    }
}

void LED_blink_task()
{
    // const uint32_t interval_on_ms = 1000;
    // const uint32_t interval_off_ms = 2000;
    // static uint32_t start_ms = 0;

    // // Blink every interval ms
    // if (board_millis() - start_ms < interval_off_ms)
    //     return; // not enough time

    // if (led_state)
    // {
    //     start_ms += interval_off_ms;
    // }
    // else
    // {
    //     start_ms += interval_on_ms;
    // }

    // gpio_put(PICO_DEFAULT_LED_PIN, !led_state);
    // led_state = 1 - led_state; // toggle
}
