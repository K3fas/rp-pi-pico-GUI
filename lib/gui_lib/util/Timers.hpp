#pragma once

#include <tuple>
#include <string>
#include <unordered_map>
#include <rp_logger.hpp>

namespace rpgui::util
{
    class Timers
    {
    private:

    public:
        std::vector<std::pair<std::string, uint64_t>> stamps;
        const rplog::Level logLevel = rplog::Level::TRACE;

        Timers() = default;
        Timers(const Timers&) = delete;
        ~Timers() = default;

        uint8_t AddStamp(const std::string& name);
        void Stamp(const std::string& name);
        void Stamp(const uint8_t at);
        void PrintStamps() const;
    };
    
    
} // namespace rpgui::util


