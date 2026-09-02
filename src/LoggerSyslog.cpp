#include "LoggerSyslog.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>

void LoggerSyslog::start(const char *name)
{
    openlog(name, LOG_PID, LOG_USER);
}

void LoggerSyslog::print(LoggerAbstract::Level level, const char *file, int line, const char *buffer)
{
    switch (level)
    {
    case LoggerAbstract::Level::ERROR:
        syslog(LOG_ERR, " %s, line %d: %s", basename(file), line, buffer);
        break;
    case LoggerAbstract::Level::WARN:
        syslog(LOG_WARNING, " %s", buffer);
        break;
    case LoggerAbstract::Level::INFO:
        syslog(LOG_INFO, " %s", buffer);
        break;
    case LoggerAbstract::Level::NOTICE:
        syslog(LOG_NOTICE, " %s", buffer);
        break;
    case LoggerAbstract::Level::DBG:
        syslog(LOG_DEBUG, " %s, line %d: %s", basename(file), line, buffer);
        break;

    default:
        break;
    }
}

void LoggerSyslog::stop(void)
{
    closelog();
}
