#include "Config.h"

#include "LoggerAbstract.h"
#include "utils.h"

#include <getopt.h>
#include <stdio.h>

Config Config::instance;

/* Configuration options */
#define CONFIG_OPTION_LOG_LEVEL "l"
#define CONFIG_OPTION_LOG_SYSLOG "y"
#define CONFIG_OPTION_LOG_STDOUT "o"

#define CONFIG_OPTION_TIME_DELIVERY_LIMIT "t"
#define CONFIG_OPTION_SIZE_DELIVERY_LIMIT "s"

#define CONFIG_OPTION_MODE_TO_MODEM "u"
#define CONFIG_OPTION_MODE_FROM_MODEM "d"

#define CONFIG_OPTION_HELP "h"

/* Configuration default values */
#define CONFIG_DEFAULT_LOG_LEVEL 0
#define CONFIG_DEFAULT_LOG_SYSLOG 0
#define CONFIG_DEFAULT_LOG_STDOUT 1
#define CONFIG_DEFAULT_TIME_DELIVERY_LIMIT 500
#define CONFIG_DEFAULT_SIZE_DELIVERY_LIMIT 256
#define CONFIG_DEFAULT_MODE_TO_MODEM 0
#define CONFIG_DEFAULT_MODE_FROM_MODEM 1
#define CONFIG_DEFAULT_SHOW_HELP 0

/* GETOPT configuration line */
#define GETOPT_LINE CONFIG_OPTION_HELP CONFIG_OPTION_LOG_LEVEL ":" CONFIG_OPTION_LOG_SYSLOG                                          \
    CONFIG_OPTION_LOG_STDOUT CONFIG_OPTION_TIME_DELIVERY_LIMIT ":" CONFIG_OPTION_SIZE_DELIVERY_LIMIT ":" CONFIG_OPTION_MODE_TO_MODEM \
        CONFIG_OPTION_MODE_FROM_MODEM

/* Command line help line */
#define HELP_COMMAND                                                                                            \
                     "[-" CONFIG_OPTION_MODE_TO_MODEM "] "                                                      \
                     "[-" CONFIG_OPTION_MODE_FROM_MODEM "] "                                                    \
                     "[-" CONFIG_OPTION_TIME_DELIVERY_LIMIT " {" xstr(CONFIG_DEFAULT_TIME_DELIVERY_LIMIT) "}] " \
                     "[-" CONFIG_OPTION_SIZE_DELIVERY_LIMIT " {" xstr(CONFIG_DEFAULT_SIZE_DELIVERY_LIMIT) "}] " \
                     "[-" CONFIG_OPTION_LOG_LEVEL " {" xstr(CONFIG_DEFAULT_LOG_LEVEL) "}] "                     \
                     "[-" CONFIG_OPTION_LOG_SYSLOG "] "                                                         \
                     "[-" CONFIG_OPTION_LOG_STDOUT "] "                                                         \
                     "[-" CONFIG_OPTION_HELP "]\n"                                                              \

Config *Config::getInstance(void)
{
    return &instance;
}

Config::Error Config::init(int argc, char *argv[])
{
    Config::Error returnValue;
    char c;

    returnValue = Config::Error::E_OK;

    /* give default values */
    logLevel = CONFIG_DEFAULT_LOG_LEVEL;
    useSyslog = CONFIG_DEFAULT_LOG_SYSLOG;
    useStdout = CONFIG_DEFAULT_LOG_STDOUT;
    showHelp = CONFIG_DEFAULT_SHOW_HELP;
    /* 500 ms is default time delivey limit */
    timeDeliveryLimit = CONFIG_DEFAULT_TIME_DELIVERY_LIMIT;
    /* 256 bytes is default buffer size limit */
    bufferSizeLimit = CONFIG_DEFAULT_SIZE_DELIVERY_LIMIT;
    /* From or to MODEM, by default direction is from modem */
    fromModem = CONFIG_DEFAULT_MODE_FROM_MODEM;
    toModem = CONFIG_DEFAULT_MODE_TO_MODEM;

    while ((c = getopt(argc, argv, GETOPT_LINE)) != -1)
    {
        switch (c)
        {
        case CONFIG_OPTION_LOG_LEVEL[0]:
            /* log level */
            if (sscanf(optarg, "%d", &logLevel) != 1)
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
            }
            break;
        case CONFIG_OPTION_TIME_DELIVERY_LIMIT[0]:
            /* time delivery limit */
            if (sscanf(optarg, "%d", &timeDeliveryLimit) != 1)
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
            }
            break;
        case CONFIG_OPTION_SIZE_DELIVERY_LIMIT[0]:
            /* buffer size delivery limit */
            if (sscanf(optarg, "%d", &bufferSizeLimit) != 1)
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
            }
            break;
        case CONFIG_OPTION_LOG_SYSLOG[0]:
            /* log to syslog */
            useSyslog = 1;
            useStdout = 0;
            break;
        case CONFIG_OPTION_LOG_STDOUT[0]:
            /* log to stdout */
            useStdout = 1;
            useSyslog = 0;
            break;
        case CONFIG_OPTION_MODE_TO_MODEM[0]:
            /* to MODEM */
            toModem = 1;
            fromModem = 0;
            break;
        case CONFIG_OPTION_MODE_FROM_MODEM[0]:
            /* from MODEM */
            toModem = 0;
            fromModem = 1;
            break;
        case '?':
        case ':':
            returnValue = Config::Error::E_ARG;
            break;
        case CONFIG_OPTION_HELP[0]:
            showHelp = 1;
            break;
        default:
            returnValue = Config::Error::E_ARG;
            break;
        }
    }

    return returnValue;
}

int Config::isUseStdout(void)
{
    return useStdout;
}

int Config::getLogLevel(void)
{
    return logLevel;
}

int Config::isUseSyslog(void)
{
    return useSyslog;
}

int Config::isShowHelp(void)
{
    return showHelp;
}

int Config::getTimeDeliveryLimit(void)
{
    return timeDeliveryLimit;
}

int Config::getBufferSizeLimit(void)
{
    return bufferSizeLimit;
}

int Config::isFromModem(void)
{
    return fromModem;
}

int Config::isToModem(void)
{
    return toModem;
}

void Config::help(int argc, char *argv[])
{
    printf("%s " HELP_COMMAND, argv[0]);
    printf("\t-" CONFIG_OPTION_MODE_TO_MODEM ": to modem\n");
    printf("\t-" CONFIG_OPTION_MODE_FROM_MODEM ": from modem\n");
    printf("\t-" CONFIG_OPTION_TIME_DELIVERY_LIMIT ": time delivery limit in ms\n");
    printf("\t-" CONFIG_OPTION_SIZE_DELIVERY_LIMIT ": buffer size delivery limit in bytes\n");
    printf("\t-" CONFIG_OPTION_LOG_LEVEL " <log level>: set minimum loggeable level [DBG %d - ERROR %d], to suppress logging use %d\n", LoggerAbstract::Level::DBG, LoggerAbstract::Level::ERROR, LoggerAbstract::Level::NO_LOG);
    printf("\t-" CONFIG_OPTION_LOG_SYSLOG ": set logger to use syslog\n");
    printf("\t-" CONFIG_OPTION_LOG_STDOUT ": set logger to use stdout\n");
    printf("\t-" CONFIG_OPTION_HELP ": show help\n");
}