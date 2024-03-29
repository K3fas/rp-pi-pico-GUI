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

using namespace rplog;



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
    logger->logLevel = rplog::Level::TRACE;
    logger->AddSink(std::cout, Level::DEBUG);
    logger->AddFile("logs_verbose.txt","", Level::TRACE);
    logger->AddSink(std::cerr, Level::WARNING);
    logger->AddFile("logs_error.txt","", Level::ERROR);

    logger->Log(" LOGGER TRACE MESSAGE", rplog::Level::TRACE);
    logger->Log(" LOGGER DEBUG MESSAGE", rplog::Level::DEBUG);
    logger->Log(" LOGGER INFORMATION MESSAGE", rplog::Level::INFORMATION);
    logger->Log(" LOGGER WARNING MESSAGE", rplog::Level::WARNING);
    logger->Log(" LOGGER ERROR MESSAGE", rplog::Level::ERROR);
    logger->Log(" LOGGER CRITICAL MESSAGE", rplog::Level::CRITICAL);


    rplog::Logger::globalLogLevel = Level::WARNING;
    rplog::Logger::logTrace(std::cout, "LOGGER TRACE MESSAGE");
    rplog::Logger::logDebug(std::cout, "LOGGER DEBUG MESSAGE");
    rplog::Logger::logInfo(std::cout, "LOGGE INFORMATION MESSAGE");
    rplog::Logger::logWarning(std::cout, "LOGGER WARNING MESSAGE");
    rplog::Logger::logError(std::cout, "LOGGER ERROR MESSAGE");
    rplog::Logger::logCritical(std::cout, "LOGGER CRITICAL MESSAGE");


    auto result = logger->AddFile("text.txt");
    result = logger->AddFile("text.txt");
    std::cout << result;
    logger->Log("FILE TEST !!!", rplog::Level::INFORMATION);
    logger->CloseFiles();
    
    rplog::Logger::DisposeSD();

    // f_unmount(pSD->pcName);
    while (1)
    {

    }
}


