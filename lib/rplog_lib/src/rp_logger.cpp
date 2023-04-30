#include "rp_logger.hpp"

#include "hw_config.h"
#include "pico/stdlib.h"
#include "ff.h"
#include "f_util.h"

#include <SDWrapper.hpp>

using namespace rpgui::util;

rplog::Logger::Logger()
{
    auto res = SDWrapper::Init();
    if (FR_OK != res)
    {
        logError(std::cerr, "Failed to init SD card ! Message:");
        logError(std::cerr, FRESULT_str(res));
    }
}

rplog::Logger::~Logger()
{
    CloseFiles();
}

bool rplog::Logger::AddFile(const std::string &name, const std::string &path)
{

    auto [result, file] = SDWrapper::OpenFile(name, path);
    if (FR_OK != result)
    {
        logError(std::cerr, "Failed to add file to logger. Message:");
        logError(std::cerr, FRESULT_str(result));
        return false;
    }
    if(file)
    {
        AddSink(file);
        logDebug(std::cout, "File added to sinks");
        return true;
    }

    logError(std::cerr, "Failed to add file to sinks!");
    return false;
}

void rplog::Logger::CloseFiles()
{
    for (auto &&sink : _sinks)
    {
        auto file = get_if<FIL *const>(&sink);
        if (file)
        {
            auto result = SDWrapper::CloseFile(*file);
            if (FR_OK != result)
            {
                logError(std::cerr, "Failed to close file! ");
            }
        }
    }
}

void rplog::Logger::DisposeSD()
{
    SDWrapper::Dispose();
}

void rplog::Logger::AddSink(FIL *file, Level logLevel)
{
    _sinks.push_back(std::make_tuple(file, logLevel));
}

void rplog::Logger::AddSink(std::ostream &stream, Level logLevel)
{
    _sinks.push_back(std::make_tuple(&stream, logLevel));
}

void rplog::Logger::Log(const std::string &message, const Level &severity)
{
    if (logLevel > severity)
        return;

    auto toPrint = levelToString(severity) + message + "\n";
    for (auto &[sink, level] : _sinks)
    {
        if(level > severity)
            continue;
        
        auto file = *(get_if<FIL *const>(&sink));
        if (file)
        {
            f_printf(file, toPrint.c_str());
            continue;
        }

        auto stream = get_if<std::ostream *const>(&sink);
        if (stream)
        {
            **stream << toPrint;
        }
    }
}

void rplog::Logger::log(FIL *const file, const std::string &message, const Level severity)
{
    printToFile(file, message, severity);
}
void rplog::Logger::log(std::ostream &stream, const std::string &message, const Level severity)
{
    printToStream(stream, message, severity);
}
void rplog::Logger::logTrace(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::TRACE);
}

void rplog::Logger::logTrace(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::TRACE);
}

void rplog::Logger::logDebug(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::DEBUG);
}

void rplog::Logger::logDebug(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::DEBUG);
}

void rplog::Logger::logInfo(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::INFORMATION);
}

void rplog::Logger::logInfo(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::INFORMATION);
}

void rplog::Logger::logWarning(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::WARNING);
}

void rplog::Logger::logWarning(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::WARNING);
}

void rplog::Logger::logError(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::ERROR);
}

void rplog::Logger::logError(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::ERROR);
}

void rplog::Logger::logCritical(FIL *file, const std::string &message)
{
    printToFile(file, message, Level::CRITICAL);
}

void rplog::Logger::logCritical(std::ostream &stream, const std::string &message)
{
    printToStream(stream, message, Level::CRITICAL);
}

inline const std::string rplog::Logger::levelToString(const Level &level)
{
    switch (level)
    {
    case TRACE:
        return "[TRACE] ";
    case DEBUG:
        return "[DEBUG] ";
    case INFORMATION:
        return "[INFORMATION] ";
    case WARNING:
        return "[WARNING] ";
    case ERROR:
        return "[ERROR] ";
    case CRITICAL:
        return "[CRITICAL] ";

    default:
        return "";
    }
}

inline void rplog::Logger::printToFile(FIL *const file, const std::string &message, const Level severity)
{
    if (rplog::Logger::globalLogLevel > severity)
        return;
    auto toPrint = levelToString(severity) + message + "\n";
    f_printf(file, toPrint.c_str());
}

inline void rplog::Logger::printToStream(std::ostream &stream, const std::string &message, const Level severity)
{
    if (rplog::Logger::globalLogLevel > severity)
        return;
    auto toPrint = levelToString(severity) + message;
    stream << toPrint << std::endl;
}
