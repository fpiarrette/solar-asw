
#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerAbstract.h"
#include "LoggerStdout.h"
#include "LoggerSyslog.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define LOGGER_ID_STDOUT (1U)
#define LOGGER_ID_SYSLOG (2U)

#define LOGGER_DEBUG_ERRNO                                                     \
    do                                                                         \
    {                                                                          \
        Logger::getInstance()->debug("errno: %d, %s", errno, strerror(errno)); \
    } while (0)

class Logger
{
public:
    static LoggerAbstract *getInstance(void);
    static void config(int loggerId);

protected:
private:
    static LoggerAbstract *instance;
    static LoggerStdout loggerStdout;
    static LoggerSyslog loggerSyslog;
};

#endif
