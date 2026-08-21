
#ifndef LOGGER_SYSLOG_H
#define LOGGER_SYSLOG_H

#include "LoggerAbstract.h"

class LoggerSyslog : public LoggerAbstract
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
