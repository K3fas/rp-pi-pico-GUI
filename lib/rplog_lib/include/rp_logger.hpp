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

    using Sink = std::tuple<std::variant<std::ostream *const, FIL *const>, Level>;

    class Logger
    {

    private:
        std::vector<Sink> _sinks;

    public:
        Level logLevel = Level::TRACE;
        inline static Level globalLogLevel = Level::TRACE;

    public:
        Logger();
        Logger(const Logger&) = delete;
        ~Logger();



        bool AddFile(const std::string& name, const std::string& path = "", Level logLevel = Level::DEBUG);
        void CloseFiles();
        static void DisposeSD();

        void AddSink(FIL *const file, Level logLevel = Level::DEBUG);
        void AddSink(std::ostream &stream, Level logLevel = Level::DEBUG);
        // Logs message to files, where log level is lower than current log level
        void Log(const std::string &message, const Level &severity);


        static void log(FIL* const file, const std::string& message, const Level severity = Level::DEBUG);
        static void log(std::ostream &stream, const std::string& message, const Level severity = Level::DEBUG);
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