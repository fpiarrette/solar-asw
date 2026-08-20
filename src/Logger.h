
#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerAbstract.h"
#include "LoggerStdout.h"
#include "LoggerSyslog.h"

#include <stdlib.h>

#define LOGGER_ID_STDOUT (1U)
#define LOGGER_ID_SYSLOG (2U)

class Logger
{
public:
    static void config(int loggerId);
    static LoggerAbstract *instance;

protected:
private:
    static LoggerStdout loggerStdout;
    static LoggerSyslog loggerSyslog;
};

#endif
