#include "Process.h"
#include "Signals.h"

#include "utils.h"

void Process::execute(void)
{
    /* perform process initialization */
    Signals::getInstance()->init();
    channelSocket.init();
    channelSpi.init();
    init();
    /* start process components */
    channelSocket.start();
    channelSpi.start();
    start();

    /* process main loop */
    while (!Signals::getInstance()->isTerminated())
    {
        if (!Signals::getInstance()->isStopped())
        {
            /* run process and return */
            run();
        }
        else
        {
            /* sleep for 100mS */
            utils_sleep(100);
        }
    }

    /* stop process components */
    stop();
    channelSocket.stop();
    channelSpi.stop();
}

void Process::init(void)
{
}

void Process::start(void)
{
}

void Process::stop(void)
{
}
