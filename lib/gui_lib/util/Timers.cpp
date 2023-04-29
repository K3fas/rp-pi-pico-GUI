#include "Timers.hpp"

#include <stdio.h>
#include "pico/stdlib.h"

uint8_t rpgui::util::Timers::AddStamp(const std::string &name)
{
    stamps.push_back(std::make_pair(name, 0));
    return stamps.size() - 1;
}

void rpgui::util::Timers::Stamp(const std::string &name)
{
    for (auto &&stamp : stamps)
    {
        if (stamp.first == name)
        {
            stamp.second = time_us_64();
            return;
        }
    }
}

void rpgui::util::Timers::Stamp(const uint8_t at)
{
    stamps[at].second = time_us_64();
}

void rpgui::util::Timers::PrintStamps() const
{
    uint64_t prev = 0;
    for (const auto &[key, value] : stamps)
    {
        if (prev == 0)
        {
            rplog::Logger::logTrace(std::cout, "Logging timing report:");
            rplog::Logger::logTrace(std::cout, key + " at: " + std::to_string(value));
            prev = value;
            continue;
        }
        rplog::Logger::logTrace(std::cout, key + " \ttook:\t " + std::to_string(value - prev) + " \tus " + std::to_string((value - prev) *100 / 16000)+ "% of a frame");
        prev = value;
    }
}
