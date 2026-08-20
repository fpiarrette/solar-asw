#include "Logger.h"

#include <stdio.h>

LoggerAbstract *Logger::instance = NULL;

LoggerStdout Logger::loggerStdout;
LoggerSyslog Logger::loggerSyslog;

LoggerAbstract *Logger::getInstance(void)
{
    return instance;
}

void Logger::config(int loggerId)
{
    if (instance == NULL)
        switch (loggerId)
        {
        case LOGGER_ID_STDOUT:
            instance = &loggerStdout;
            break;
        case LOGGER_ID_SYSLOG:
            instance = &loggerSyslog;
            break;
        default:
            fprintf(stderr, "Error configuring Logger with id %d\n", loggerId);
            break;
        }
}
