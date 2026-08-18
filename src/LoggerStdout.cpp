#include "LoggerStdout.h"

#include <stdio.h>
#include <stdarg.h>

void LoggerStdout::init(void)
{
}

void LoggerStdout::start(const char *name)
{
}

void LoggerStdout::stop(void)
{
}

void LoggerStdout::error(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    printf("ERR: %s\n", buffer);
}

void LoggerStdout::warning(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    printf("WARN: %s\n", buffer);
}

void LoggerStdout::info(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    printf("INFO: %s\n", buffer);
}

void LoggerStdout::notice(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    printf("NOTICE: %s\n", buffer);
}

void LoggerStdout::debug(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    int rc = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    printf("DBG: %s\n", buffer);
}