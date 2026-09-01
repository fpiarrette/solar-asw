#include "Config.h"
#include "Logger.h"
#include "ProcessToModem.h"
#include "ProcessFromModem.h"
#include "ContextToModem.h"
#include "ContextHost.h"
#include "ContextFromModem.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* parse arguments */
    if (Config::getInstance()->init(argc, argv) == Config::Error::E_OK)
    {

        /* initialization */
        if (Config::getInstance()->isUseStdout())
            Logger::config(Logger::Type::STDOUT);
        else
            Logger::config(Logger::Type::SYSLOG);

        Logger::getInstance()->init();
        Logger::getInstance()->setLevel(Config::getInstance()->getLogLevel());
        Logger::getInstance()->start("Modem TCP converter");

        L_INFO("Starting...");

        if (Config::getInstance()->isShowHelp())
        {
            Config::getInstance()->help(argc, argv);
        }
        else
        {

            Process *process;
            Context *context;
            ProcessFromModem processFromModem;
            ContextFromModem contextFromModem;
            ProcessToModem processToModem;
            ContextToModem contextToModem;

            ContextHost contextHost;

            if (Config::getInstance()->isFromModem())
            {
                processFromModem.setTimeDeliveryLimit(Config::getInstance()->getTimeDeliveryLimit());
                processFromModem.setBufferSizeLimit(Config::getInstance()->getBufferSizeLimit());
                process = &processFromModem;
                context = &contextFromModem;
            }
            else
            {
                process = &processToModem;
                context = &contextToModem;
            }

#ifdef FORCE_TEST_CONTEXT
            /* This compile time option allows to overwrite proper context and configure the process with a test context just for host platform and debug purpose */
            L_INFO("Using fake host context");
            context = &contextHost;
#endif

            /* execute process includling initialization, start, running and stop */
            process->execute(context);
        }

        L_INFO("Finishing...");
        Logger::getInstance()->stop();
    }
    else
    {
        Config::getInstance()->help(argc, argv);
    }

    return EXIT_SUCCESS;
}
