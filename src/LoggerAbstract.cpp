#include "LoggerAbstract.h"

#include <stdio.h>
#include <stdarg.h>

void LoggerAbstract::error(const char *format, ...)
{
    if (isAllowed(Level::ERROR))
    {
        va_list args;
        va_start(args, format);
        logError(format, args);
        va_end(args);
    }
}

void LoggerAbstract::warning(const char *format, ...)
{
    if (isAllowed(Level::WARN))
    {
        va_list args;
        va_start(args, format);
        logWarning(format, args);
        va_end(args);
    }
}

void LoggerAbstract::info(const char *format, ...)
{
    if (isAllowed(Level::INFO))
    {
        va_list args;
        va_start(args, format);
        logInfo(format, args);
        va_end(args);
    }
}

void LoggerAbstract::notice(const char *format, ...)
{
    if (isAllowed(Level::NOTICE))
    {
        va_list args;
        va_start(args, format);
        logNotice(format, args);
        va_end(args);
    }
}

void LoggerAbstract::debug(const char *format, ...)
{
    if (isAllowed(Level::DBG))
    {
        va_list args;
        va_start(args, format);
        logDebug(format, args);
        va_end(args);
    }
}

void LoggerAbstract::setLevel(int l)
{
    level = l;
}

int LoggerAbstract::isAllowed(Level l)
{
    return l >= level;
}
