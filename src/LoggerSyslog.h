
#ifndef LOGGER_SYSLOG_H
#define LOGGER_SYSLOG_H

#include "LoggerAbstract.h"

class LoggerSyslog : public LoggerAbstract
{
public:
    void init(void);
    void start(const char *name);
    void stop(void);

    void error(const char *format, ...);
    void warning(const char *format, ...);
    void info(const char *format, ...);
    void notice(const char *format, ...);
    void debug(const char *format, ...);
};

#endif
