#pragma once

#include <tuple>
#include <string>
#include <map>
#include <rp_logger.hpp>

namespace rpgui::util
{
    class Timers
    {
    private:
    public:
        std::map<std::string, uint64_t> stamps;

        Timers() = default;
        Timers(const Timers&) = delete;
        ~Timers() = default;

        void AddStamp(const std::string& name);
        void Stamp(const std::string& name);
        void PrintStamps();
    };
    
    
} // namespace rpgui::util


