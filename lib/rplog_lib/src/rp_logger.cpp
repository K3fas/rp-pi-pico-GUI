#include "rp_logger.hpp"

#include "hw_config.h"
#include "pico/stdlib.h"
#include "ff.h"
#include "f_util.h"

rplog::Logger::~Logger()
{
    CloseFiles();
}

bool rplog::Logger::InitSD()
{
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr)
    {
        logError(std::cerr, "Failed initialize SD card! Message:");
        logError(std::cerr, FRESULT_str(fr));
        _sdInit = false;
        return false;
    }

    logDebug(std::cout, "SD Card initialized");
    _sdInit = true;
    return true;
}

void rplog::Logger::CloseSD()
{
    if (_sdInit)
    {
        sd_card_t *pSD = sd_get_by_num(0);
        f_unmount(pSD->pcName);
        logDebug(std::cout, "SD Card closed");
    }
}

FIL *rplog::Logger::OpenFile(const std::string &path)
{
    if(!_sdInit)
        return nullptr;
    
    auto fil = new FIL;
    auto fr = f_open(fil, path.c_str(), FA_OPEN_APPEND | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr)
    {
        logError(std::cerr, "Failed to open file! Message:");
        logError(std::cerr, FRESULT_str(fr));
        return nullptr;
    }
    logDebug(std::cout, "Opened file");
    return fil;
}

bool rplog::Logger::AddFile(const std::string &path)
{
    if(!_sdInit)
        return false;
    
    auto file = OpenFile(path);
    if (file)
    {
        _sinks.push_back(file);
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
            auto fr = f_close(*file);
            if (FR_OK != fr)
            {
                logError(std::cerr, "Failed to close file! Message:");
                logError(std::cerr, FRESULT_str(fr));
            }
        }
    }
}

void rplog::Logger::AddSink(FIL *file)
{
    _sinks.push_back(file);
}

void rplog::Logger::AddSink(std::ostream &stream)
{
    _sinks.push_back(&stream);
}

void rplog::Logger::Log(const std::string &message, const Level &severity)
{
    if (logLevel > severity)
        return;

    auto toPrint = levelToString(severity) + message + "\n";
    for (auto &&sink : _sinks)
    {

        auto file = get_if<FIL *const>(&sink);
        if (file)
        {
            f_printf(*file, toPrint.c_str());
            continue;
        }

        auto stream = get_if<std::ostream *const>(&sink);
        if (stream)
        {
            **stream << toPrint;
        }
    }
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
    if(rplog::Logger::globalLogLevel < severity)
        return;
    auto toPrint = levelToString(severity) + message + "\n";
    f_printf(file, toPrint.c_str());
}

inline void rplog::Logger::printToStream(std::ostream &stream, const std::string &message, const Level severity)
{
    if(rplog::Logger::globalLogLevel < severity)
        return;
    auto toPrint = levelToString(severity) + message + "\n";
    stream << toPrint;
}
