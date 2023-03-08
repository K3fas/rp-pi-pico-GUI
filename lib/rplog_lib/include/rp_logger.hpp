//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RPLOGGER_HPP
#define PICO_KIT_FRAMEWORK_RPLOGGER_HPP

#include "stdint.h"
#include <string>

namespace rplog
{

    class FIL;

    enum class Level : uint8_t
    {
        Trace,
        Debug,
        Inforamtion,
        Warning,
        Error,
        Critical,
        None,
    };

    void logTrace(FIL &file, const std::string &message);
    // void logDebug();
    // void logInfo();
    // void logWarning();
    // void logError();
    // void logCritical();

    class Logger
    {
    private:
        /* data */
    public:
        Logger(/* args */);
        ~Logger();

        void Log(const std::string &message);
    };

} // namespace rplog

#endif // PICO_KIT_FRAMEWORK_RPLOGGER_HPP