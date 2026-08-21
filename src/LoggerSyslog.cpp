#include "LoggerSyslog.h"

#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

void LoggerSyslog::init(void)
{
}

void LoggerSyslog::start(const char *name)
{
    openlog(name, LOG_PID, LOG_USER);
}

void LoggerSyslog::stop(void)
{
    closelog();
}

void LoggerSyslog::logError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    syslog(LOG_ERR, format, args);
    va_end(args);
}

void LoggerSyslog::logWarning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    syslog(LOG_WARNING, format, args);
    va_end(args);
}

void LoggerSyslog::logInfo(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    syslog(LOG_INFO, format, args);
    va_end(args);
}

void LoggerSyslog::logNotice(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    syslog(LOG_NOTICE, format, args);
    va_end(args);
}

void LoggerSyslog::logDebug(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    syslog(LOG_DEBUG, format, args);
    va_end(args);
}