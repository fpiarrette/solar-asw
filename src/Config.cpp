#include "Config.h"

#include <getopt.h>
#include <stdio.h>

Config Config::instance;

Config *Config::getInstance(void)
{
    return &instance;
}

Config::Error Config::init(int argc, char *argv[])
{
    Config::Error returnValue;

    returnValue = Config::Error::E_OK;

    /* give default values */
    logLevel = 0;
    useSyslog = 0;
    useStdout = 1;
    showHelp = 0;
    /* 500 ms is default time delivey limit */
    timeDeliveryLimit = 500;
    /* 256 bytes is default buffer size limit */
    bufferSizeLimit = 256;
    /* From or to MODEM, by default direction is from modem */
    fromModem = 1;
    toModem = 0;

    for (;;)
    {
        switch (getopt(argc, argv, "hl:sdt:b:uf"))
        {
        case 'l':
            /* log level */
            if (sscanf(optarg, "%d", &logLevel) == 1)
            {
                /* parsed correctly */
                continue;
            }
            else
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
                break;
            }
        case 't':
            /* time delivery limit */
            if (sscanf(optarg, "%d", &timeDeliveryLimit) == 1)
            {
                /* parsed correctly */
                continue;
            }
            else
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
                break;
            }
        case 'b':
            /* buffer size delivery limit */
            if (sscanf(optarg, "%d", &bufferSizeLimit) == 1)
            {
                /* parsed correctly */
                continue;
            }
            else
            {
                /* not parsed correctly */
                returnValue = Config::Error::E_ARG;
                break;
            }
        case 's':
            /* log to syslog */
            useSyslog = 1;
            useStdout = 0;
            continue;
        case 'd':
            /* log to stdout */
            useStdout = 1;
            useSyslog = 0;
            continue;
        case 'u':
            /* to MODEM */
            toModem = 1;
            fromModem = 0;
            continue;
        case 'm':
            /* from MODEM */
            toModem = 0;
            fromModem = 1;
            continue;
        case '?':
        case ':':
            returnValue = Config::Error::E_ARG;
            break;
        case 'h':
            showHelp = 1;
            break;
        default:

            break;
        case -1:
            break;
        }
    }

    return returnValue;
}

int Config::isUseStdout(void)
{
    return useStdout;
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
    printf("%s [-h] [-l {0}] [-s] [-d] [-t {500}] [-b {256}] [-u] [-m]\n", argv[0]);
    printf("\t-h: show help\n");
    printf("\t-l <log level>: set log level\n");
    printf("\t-s: set logger to use syslog\n");
    printf("\t-d: set logger to use stdout\n");
    printf("\t-t: time delivery limit in ms\n");
    printf("\t-b: buffer size delivery limit in bytes\n");
    printf("\t-u: to modem\n");
    printf("\t-m: from modem\n");
}