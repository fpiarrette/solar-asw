#include "Logger.h"

#include <stdio.h>

LoggerAbstract *Logger::instance = NULL;

LoggerStdout Logger::loggerStdout;
LoggerSyslog Logger::loggerSyslog;

LoggerAbstract *Logger::getInstance(void)
{
    return instance;
}

void Logger::config(Type loggerType)
{
    if (instance == NULL)
        switch (loggerType)
        {
        case Logger::Type::STDOUT:
            instance = &loggerStdout;
            break;
        case Logger::Type::SYSLOG:
            instance = &loggerSyslog;
            break;
        default:
            fprintf(stderr, "Error configuring Logger with id %d\n", loggerType);
            break;
        }
}
