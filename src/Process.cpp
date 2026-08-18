#include "Process.h"
#include "Signals.h"

#include "utils.h"

void Process::execute(void)
{
    /* perform process initialization */
    init();
    /* start process components */
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
}

void Process::init(void)
{
    Signals::getInstance()->init();
    channelSocket.init();
    channelSpi.init();
}

void Process::start(void)
{
    channelSocket.start();
    channelSpi.start();
}

void Process::stop(void)
{
    channelSocket.stop();
    channelSpi.stop();
}
