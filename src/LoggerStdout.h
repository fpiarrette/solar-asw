
#ifndef LOGGER_STDOUT_H
#define LOGGER_STDOUT_H

#include "LoggerAbstract.h"

class LoggerStdout : public LoggerAbstract
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

protected:
private:
};

#endif
