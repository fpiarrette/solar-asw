
#ifndef LOGGER_ABSTRACT_H
#define LOGGER_ABSTRACT_H

#include <stdarg.h>

#define LOGGER_LEVEL_VALUE_NO_LOG 6
#define LOGGER_LEVEL_VALUE_ERROR 5
#define LOGGER_LEVEL_VALUE_WARN 4
#define LOGGER_LEVEL_VALUE_INFO 3
#define LOGGER_LEVEL_VALUE_NOTICE 2
#define LOGGER_LEVEL_VALUE_DBG 1

class LoggerAbstract
{
public:
    enum Level
    {
        NO_LOG = LOGGER_LEVEL_VALUE_NO_LOG,
        ERROR = LOGGER_LEVEL_VALUE_ERROR,
        WARN = LOGGER_LEVEL_VALUE_WARN,
        INFO = LOGGER_LEVEL_VALUE_INFO,
        NOTICE = LOGGER_LEVEL_VALUE_NOTICE,
        DBG = LOGGER_LEVEL_VALUE_DBG
    };

    virtual void start(const char *name) = 0;
    void log(LoggerAbstract::Level level, const char *file, int line, const char *format, ...);
    virtual void stop(void) = 0;

    void setLevel(int l);
    int isAllowed(Level l);

protected:
    void compose(LoggerAbstract::Level level, const char *file, int line, const char *format, va_list args);
    virtual void print(LoggerAbstract::Level level, const char *file, int line, const char *buffer) = 0;
    int level;

private:
};

#endif
