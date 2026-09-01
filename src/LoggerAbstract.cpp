#include "LoggerAbstract.h"

#include <stdio.h>
#include <stdarg.h>

void LoggerAbstract::log(LoggerAbstract::Level level, const char *format, ...)
{
    if (isAllowed(level))
    {
        va_list args;
        va_start(args, format);
        compose(level, format, args);
        va_end(args);
    }
}

void LoggerAbstract::compose(LoggerAbstract::Level level, const char *format, va_list args)
{
    char buffer[4096];
    int rc;
    rc = vsnprintf(buffer, sizeof(buffer), format, args);
    (void) rc;
    /* FIXME check return */
    print(level, buffer);
}

void LoggerAbstract::setLevel(int l)
{
    if (l <= Level::NO_LOG && l >= Level::DBG)
        level = l;
    else
    {
        /* any other level is discarded */
    }
}

int LoggerAbstract::isAllowed(Level l)
{
    return l >= level;
}
