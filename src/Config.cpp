#include "Config.h"

#include <getopt.h>
#include <stdio.h>

Config Config::instance;

Config *Config::getInstance(void)
{
    return &instance;
}

int Config::init(int argc, char *argv[])
{
    int returnValue;

    returnValue = CONFIG_E_OK;

    /* give default values */
    logLevel = 0;
    useSyslog = 0;
    useStdout = 1;
    showHelp = 0;

    for (;;)
    {
        switch (getopt(argc, argv, "hl:sd"))
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
                returnValue = CONFIG_E_INVALID;
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
        case '?':
        case ':':
            returnValue = CONFIG_E_INVALID;
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

void Config::help(int argc, char *argv[])
{
    printf("%s [-h] [-l {0}] [-s] [-d]\n", argv[0]);
    printf("\t-h: show help\n");
    printf("\t-l <log level>: set log level\n");
    printf("\t-s: set logger to use syslog\n");
    printf("\t-d: set logger to use stdout\n");
}