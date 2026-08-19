#include "Process.h"
#include "Signals.h"

#include "utils.h"

void Process::execute(void)
{
    long int start_time, now;

    /* perform process initialization */
    Signals::getInstance()->init();
    channelSocket.init();
    channelSpi.init();

    /* start process components */
    channelSocket.start();
    channelSpi.start();
    start();

    /* get start time in ms */
    start_time = utils_curr_time_in_ms();

    /* process main loop */
    while (!Signals::getInstance()->isTerminated())
    {
        if (!Signals::getInstance()->isStopped())
        {
            /* obtain current time in ms */
            now = utils_curr_time_in_ms();
            /* run process and return */
            run(now - start_time);
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
