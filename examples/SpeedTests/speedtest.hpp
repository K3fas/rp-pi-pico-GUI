#pragma once

#include <rp_logger.hpp>
#include "Timers.hpp"

using namespace rplog;

namespace rpgui::common
{
    class View;
}

class SpeedTester
{
    private:
    Logger logger;
public:

    struct speedResults
    {
        uint64_t total,average, midrange, max = 0, min = -1;
    };

    SpeedTester() = delete;
    SpeedTester(const SpeedTester&) = delete;
    ~SpeedTester();

    SpeedTester(std::string logFile);

    speedResults PerformTest(rpgui::common::View *elements[], uint16_t count, uint16_t runs, const std::string& elementName);

    void LogResults(const speedResults& results, const std::string& elementName);

};


