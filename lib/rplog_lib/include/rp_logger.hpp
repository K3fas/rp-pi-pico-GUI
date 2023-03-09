//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RPLOGGER_HPP
#define PICO_KIT_FRAMEWORK_RPLOGGER_HPP

#include "stdint.h"
#include <iostream>
#include <string>
#include <vector>

#include "ff.h"

namespace rplog
{
    enum Level : uint8_t
    {
        TRACE,
        DEBUG,
        INFORMATION,
        WARNING,
        ERROR,
        CRITICAL,
        None,
    };

    void logTrace(FIL *file, const std::string &message);
    // void logTrace(FIL *file, const char *message);
    void logTrace(std::ostream &sink, const std::string &message);
    // void logDebug();
    // void logInfo();
    // void logWarning();
    // void logError();
    // void logCritical();

    class Logger
    {
        struct LogFile
        {
            FIL *file;
            Level logLevel;
        };

    private:
        std::vector<LogFile> _files;

    public:
        Level logLevel;

    public:
        Logger() = default;
        ~Logger() = default;

        void AddLoggingFile(FIL *file, const Level logLevel);
        // Logs message to files, where log level is lower than current log level
        void Log(const std::string &message);
        void Log(const std::string &message, Level logLevel);

    private:
        inline static std::string levelToString(const Level &level)
        {
            switch (level)
            {
            case TRACE:
                return "TRACE";
            case DEBUG:
                return "DEBUG";
            case INFORMATION:
                return "INFORMATION";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";

            default:
                return "";
            }
        }
    };

} // namespace rplog

#endif // PICO_KIT_FRAMEWORK_RPLOGGER_HPP