
#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerAbstract.h"
#include "LoggerStdout.h"
#include "LoggerSyslog.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define L_ERROR(m, ...)                                 \
    do                                                  \
    {                                                   \
        Logger::getInstance()->error(m, ##__VA_ARGS__); \
    } while (0)

#define L_WARNING(m, ...)                                 \
    do                                                    \
    {                                                     \
        Logger::getInstance()->warning(m, ##__VA_ARGS__); \
    } while (0)

#define L_INFO(m, ...)                                 \
    do                                                 \
    {                                                  \
        Logger::getInstance()->info(m, ##__VA_ARGS__); \
    } while (0)

#define L_NOTICE(m, ...)                                 \
    do                                                   \
    {                                                    \
        Logger::getInstance()->notice(m, ##__VA_ARGS__); \
    } while (0)

#define L_DEBUG(m, ...)                                 \
    do                                                  \
    {                                                   \
        Logger::getInstance()->debug(m, ##__VA_ARGS__); \
    } while (0)

#define LOGGER_DEBUG_ERRNO                                                     \
    do                                                                         \
    {                                                                          \
        Logger::getInstance()->debug("errno: %d, %s", errno, strerror(errno)); \
    } while (0)

class Logger
{
public:
    enum Type
    {
        STDOUT = 1,
        SYSLOG = 2
    };
    static LoggerAbstract *getInstance(void);
    static void config(Type loggerType);

protected:
private:
    static LoggerAbstract *instance;
    static LoggerStdout loggerStdout;
    static LoggerSyslog loggerSyslog;
};

#endif
