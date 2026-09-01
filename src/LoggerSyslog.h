
#ifndef LOGGER_SYSLOG_H
#define LOGGER_SYSLOG_H

#include "LoggerAbstract.h"

class LoggerSyslog : public LoggerAbstract
{
public:
    void init(void);
    void start(const char *name);
    void print(LoggerAbstract::Level level, const char *file, int line, const char *buffer);
    void stop(void);

protected:
private:
};

#endif
