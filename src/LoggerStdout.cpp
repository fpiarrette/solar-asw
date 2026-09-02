#include "LoggerStdout.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void LoggerStdout::start(const char *name)
{
}

void LoggerStdout::print(LoggerAbstract::Level level, const char *file, int line, const char *buffer)
{
    switch (level)
    {
    case LoggerAbstract::Level::ERROR:
        printf("ERR: %s, line %d: %s\n", basename(file), line, buffer);
        break;
    case LoggerAbstract::Level::WARN:
        printf("WARN: %s\n", buffer);
        break;
    case LoggerAbstract::Level::INFO:
        printf("INFO: %s\n", buffer);
        break;
    case LoggerAbstract::Level::NOTICE:
        printf("NOTICE: %s\n", buffer);
        break;
    case LoggerAbstract::Level::DBG:
        printf("DBG: %s, line %d: %s\n", basename(file), line, buffer);
        break;

    default:
        break;
    }
}

void LoggerStdout::stop(void)
{
}
