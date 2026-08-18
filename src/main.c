#include "Logger.h"
#include "ProcessToModem.h"
#include "ProcessFromModem.h"

#include <stdlib.h>

int main(void)
{
    /* Initialization */
    Logger::config(LOGGER_ID_STDOUT);
    Logger::instance->init();
    Logger::instance->start("Modem TCP converter");

    Logger::instance->info("Starting...");

#ifdef PROCESS_TO_MODEM
    ProcessToModem process;
#else
    ProcessFromModem process;
#endif

    /* execute process includling initialization, start, running and stop */
    process.execute();

    Logger::instance->info("Finishing...");
    Logger::instance->stop();

    return EXIT_SUCCESS;
}
