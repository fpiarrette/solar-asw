#include "Logger.h"
#include "ProcessToModem.h"
#include "ProcessFromModem.h"

#include <stdlib.h>

int main(void)
{
    /* Initialization */
    Logger::config(LOGGER_ID_STDOUT);

#ifdef PROCESS_TO_MODEM
    ProcessToModem process;
#else
    ProcessFromModem process;
#endif

    /* execute process includling initialization, start, running and stop */
    process.execute();

    return EXIT_SUCCESS;
}
