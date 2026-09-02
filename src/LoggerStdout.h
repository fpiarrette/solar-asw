
#ifndef LOGGER_STDOUT_H
#define LOGGER_STDOUT_H

#include "LoggerAbstract.h"

class LoggerStdout : public LoggerAbstract
{
public:
    void start(const char *name);
    void print(LoggerAbstract::Level level, const char *file, int line, const char *buffer);
    void stop(void);

protected:
private:
};

#endif
