
#ifndef LOGGER_STDOUT_H
#define LOGGER_STDOUT_H

#include "LoggerAbstract.h"

class LoggerStdout : public LoggerAbstract
{
public:
    void init(void);
    void start(const char *name);
    void stop(void);

    void logError(const char *format, ...);
    void logWarning(const char *format, ...);
    void logInfo(const char *format, ...);
    void logNotice(const char *format, ...);
    void logDebug(const char *format, ...);

protected:
private:
};

#endif
