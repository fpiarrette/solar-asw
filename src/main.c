#include "Config.h"
#include "Logger.h"
#include "ProcessToModem.h"
#include "ProcessFromModem.h"
#include "ContextToModem.h"
#include "ContextFromModem.h"

#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* parse arguments */
    if (Config::getInstance()->init(argc, argv) == CONFIG_E_OK)
    {

        /* initialization */
        if (Config::getInstance()->isUseStdout())
            Logger::config(LOGGER_ID_STDOUT);
        else
            Logger::config(LOGGER_ID_SYSLOG);

        Logger::instance->init();
        Logger::instance->start("Modem TCP converter");

        Logger::instance->info("Starting...");

        if (Config::getInstance()->isShowHelp())
        {
            Config::getInstance()->help(argc, argv);
        }
        else
        {

#ifdef PROCESS_TO_MODEM
            ProcessToModem process;
#else
            ProcessFromModem process;
            process.setTimeDeliveryLimit(Config::getInstance()->getTimeDeliveryLimit());
            process.setBufferSizeLimit(Config::getInstance()->getBufferSizeLimit());
#endif

#ifdef PROCESS_TO_MODEM
            ContextToModem context;
#else
            ContextFromModem context;
#endif

            /* execute process includling initialization, start, running and stop */
            process.execute(&context);
        }

        Logger::instance->info("Finishing...");
        Logger::instance->stop();
    }
    else
    {
        Config::getInstance()->help(argc, argv);
    }

    return EXIT_SUCCESS;
}
