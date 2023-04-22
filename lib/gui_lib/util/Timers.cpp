#include "Timers.hpp"

#include <stdio.h>
#include "pico/stdlib.h"

void rpgui::util::Timers::AddStamp(const std::string &name)
{
    stamps[name] = 0;
}

void rpgui::util::Timers::Stamp(const std::string &name)
{
    stamps[name] = time_us_64();
}

void rpgui::util::Timers::PrintStamps()
{
    uint64_t prev = 0;
    for (auto &&[key, value] : stamps)
    {
        if(prev == 0)
        {
            rplog::Logger::logTrace(std::cout, "Logging timing report:");
            rplog::Logger::logTrace(std::cout, key + " at: " + std::to_string(value));
            prev = value;
            continue;
        }
        rplog::Logger::logTrace(std::cout, key + " took: " + std::to_string(value - prev));
        prev = value;
    }
    
}
