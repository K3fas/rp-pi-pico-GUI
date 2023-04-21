//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RPLOGGER_HPP
#define PICO_KIT_FRAMEWORK_RPLOGGER_HPP

#include "stdint.h"
#include <iostream>
#include <string>
#include <vector>
#include <variant>

#include "ff.h"

namespace rplog
{
    using Sink = std::variant<std::ostream *const, FIL *const>;

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

    class Logger
    {

    private:
        std::vector<Sink> _sinks;

    public:
        Level logLevel = Level::DEBUG;
        inline static Level globalLogLevel = Level::DEBUG;

    public:
        Logger();
        Logger(const Logger&) = delete;
        ~Logger();



        bool AddFile(const std::string& name, const std::string& path = "");
        void CloseFiles();
        static void DisposeSD();

        void AddSink(FIL *const file);
        void AddSink(std::ostream &stream);
        // Logs message to files, where log level is lower than current log level
        void Log(const std::string &message, const Level &severity);

        static void logTrace(FIL *const file, const std::string &message);
        static void logTrace(std::ostream &stream, const std::string &message);
        static void logDebug(FIL *const file, const std::string &message);
        static void logDebug(std::ostream &stream, const std::string &message);
        static void logInfo(FIL *const file, const std::string &message);
        static void logInfo(std::ostream &stream, const std::string &message);
        static void logWarning(FIL *const file, const std::string &message);
        static void logWarning(std::ostream &stream, const std::string &message);
        static void logError(FIL *const file, const std::string &message);
        static void logError(std::ostream &stream, const std::string &message);
        static void logCritical(FIL *const file, const std::string &message);
        static void logCritical(std::ostream &stream, const std::string &message);

    private:
        inline static const std::string levelToString(const Level &level);
        inline static void printToFile(FIL *const file, const std::string& message, const Level severity);
        inline static void printToStream(std::ostream& stream, const std::string& message, const Level severity);
    };

} // namespace rplog

#endif // PICO_KIT_FRAMEWORK_RPLOGGER_HPP