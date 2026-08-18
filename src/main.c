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
    ChannelSocket c2;

    c1.init();
    c2.init();

    c1.start();
    c2.start();

#ifdef PROCESS_TO_MODEM
    ProcessToModem process;
#else
    ProcessFromModem process;
#endif

    process.init();

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
            process.run();
        }
        else
        {
            /* sleep for 100mS */
            utils_sleep(100);
        }
    }

    /* stop/deallocate componets */
    c1.stop();
    c2.stop();

    process.stop();

    return 0;
}
