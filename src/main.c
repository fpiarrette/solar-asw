#include "ChannelSpi.h"
#include "ChannelSocket.h"
#include "ProcessToModem.h"
#include "ProcessFromModem.h"

#include "utils.h"

#include <signal.h>
#include <stdlib.h>

int stopped;
int terminated;

static void signal_handler(int signal)
{
    switch (signal)
    {
    case SIGINT:
        terminated = 1;
        break;
    case SIGTSTP:
        stopped = 1;
        break;
    case SIGCONT:
        stopped = 0;
        break;
    default:
        break;
    }
}

int main(void)
{
    /* Initialization */
    ChannelSpi c1;
    c1.init(NULL);
    ChannelSocket c2;
    c2.init(NULL);

    ProcessToModem processToModem;
    ProcessFromModem processFromModem;

    struct sigaction psa;
    psa.sa_handler = signal_handler;
    sigaction(SIGINT, &psa, NULL);
    sigaction(SIGTSTP, &psa, NULL);
    sigaction(SIGCONT, &psa, NULL);

    /* Main loop */
    while (!terminated)
    {
        if (!stopped)
        {
#ifdef PROCESS_TO_MODEM
            processToModem.run();
#else
            processFromModem.run();
#endif
        }
        else
        {
            /* sleep for 100mS */
            utils_sleep(100);
        }
    }

    /* stop/deallocate componets */

    return 0;
}
