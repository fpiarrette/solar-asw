
#ifndef LOGGER_STDOUT_H
#define LOGGER_STDOUT_H

#include "LoggerAbstract.h"

class LoggerStdout : public LoggerAbstract
{
public:
    void init(void);
    void start(const char *name);
    void print(LoggerAbstract::Level level, const char *buffer);
    void stop(void);

protected:
private:
};

#endif
