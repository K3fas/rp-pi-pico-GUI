#include "rp_logger.hpp"
// #include "ff.h"

void rplog::logTrace(FIL *file, const std::string &message)
{
    auto toPrint = "[TRACE] " + message + "\n";
    f_printf(file, toPrint.c_str());
}

void rplog::logTrace(std::ostream &sink, const std::string &message)
{
    sink << "[TRACE] " << message << std::endl;
}

void rplog::Logger::AddLoggingFile(FIL *file, const Level logLevel)
{
    _files.emplace_back(LogFile{file, logLevel});
}

void rplog::Logger::Log(const std::string &message)
{
    for (auto &&file : _files)
    {
        if (file.logLevel <= this->logLevel)
        {
            auto toPrint = "[" + levelToString(this->logLevel) + "] " +
                           message + "\n";
            f_printf(file.file, toPrint.c_str());
        }
    }
}

void rplog::Logger::Log(const std::string &message, Level logLevel)
{
    for (auto &&file : _files)
    {
        if (file.logLevel <= logLevel)
        {
            auto toPrint = "[" + levelToString(this->logLevel) + "] " +
                           message + "\n";
            f_printf(file.file, toPrint.c_str());
        }
    }
}
