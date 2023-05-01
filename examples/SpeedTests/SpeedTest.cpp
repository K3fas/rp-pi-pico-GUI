#include "SpeedTest.hpp"
#include <rpgui.hpp>

#include <stdio.h>
#include "pico/stdlib.h"

#include <iostream>

using namespace rplog;

SpeedTester::~SpeedTester()
{
    logger.CloseFiles();
}

SpeedTester::SpeedTester(std::string logFile)
{
    Logger::logTrace(std::cout, "Created speed tester");
    logger.AddFile(logFile, "", Level::INFORMATION);
    logger.AddSink(std::cout, Level::INFORMATION);
}

SpeedTester::speedResults SpeedTester::PerformTest(rpgui::common::VisualElement *elements[], uint16_t count, uint16_t runs, const std::string &elementName)
{
    speedResults results;

    results.total = time_us_64();
    // Counts total time
    for (size_t j = 0; j < runs; j++)
    {
        for (size_t i = 0; i < count; i++)
        {
            elements[i]->Draw();
        }
    }

    results.total = time_us_64() - results.total;
    results.average = results.total / runs;
    results.averageElement = results.average / count;
    // Run again for other calculations
    for (size_t j = 0; j < runs; j++)
    {
        for (size_t i = 0; i < count; i++)
        {
            auto start = time_us_64();
            elements[i]->Draw();
            auto iteration = time_us_64() - start;
            if (iteration > results.max)
            {
                results.max = iteration;
            }
            if (iteration < results.min)
            {
                results.min = iteration;
            }
        }
    }

    results.midrange = (results.max - results.min) / 2;
    LogResults(results, elementName);
    return results;
}

void SpeedTester::LogResults(const speedResults &results, const std::string &elementName)
{
    logger.Log("Speed test results for element: " + elementName, Level::INFORMATION);
    logger.Log("Total   : " + std::to_string(results.total / 1000) + " ms", Level::INFORMATION);
    logger.Log("Average : " + std::to_string(results.average) + " us", Level::INFORMATION);
    logger.Log("Per obj : " + std::to_string(results.averageElement) + " us", Level::INFORMATION);
    logger.Log("Max     : " + std::to_string(results.max) + " us", Level::INFORMATION);
    logger.Log("Min     : " + std::to_string(results.min) + " us", Level::INFORMATION);
    logger.Log("Mid     : " + std::to_string(results.midrange) + " us\n", Level::INFORMATION);
    logger.SaveData();
}
