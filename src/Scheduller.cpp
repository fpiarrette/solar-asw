#include "Scheduller.h"

#include "Logger.h"
#include "Signals.h"
#include "utils.h"

#include <string.h>

void Scheduller::init(void)
{
    memset(tasks, 0, sizeof(tasks));

    period = 50;

    L_DEBUG("initialized");
}

void Scheduller::addTask(Scheduller::Task *task, int executionOrder)
{
    tasks[executionOrder] = task;

    L_DEBUG("'%s' added", task->getName());
}

void Scheduller::run(void)
{
    long int startTime, elapsedTime, sleepTime;
    int n;

    L_DEBUG("staring with %d ms period", period);

    /* initialization */
    Signals::getInstance()->init();

    /* prepare all tasks */
    for (n = 0; n < SCHEDULLER_SIZE; n++)
    {
        if (tasks[n] != NULL)
        {
            tasks[n]->prepare();
        }
    }

    /* scheduller main loop */
    while (!Signals::getInstance()->isTerminated())
    {
        if (!Signals::getInstance()->isStopped())
        {
            /* get start time in ms */
            startTime = utils_curr_time_in_ms();

            for (n = 0; n < SCHEDULLER_SIZE; n++)
            {
                if (tasks[n] != NULL && tasks[n]->need(startTime))
                {
                    tasks[n]->run(startTime);
                    break;
                }
            }

            elapsedTime = utils_curr_time_in_ms() - startTime;
            sleepTime = period - elapsedTime;

            /* check at least a task was executed */
            if (n < SCHEDULLER_SIZE)
                /* update time in this case */
                tasks[n]->incrementExpendedTime(elapsedTime);

            if (sleepTime > 0)
            {
                utils_sleep(sleepTime);
            }
        }
        else
        {
            /* process stopped, just sleep for 100mS */
            utils_sleep(100);
        }
    }

    /* stop all tasks */
    for (n = 0; n < SCHEDULLER_SIZE; n++)
    {
        if (tasks[n] != NULL)
        {
            tasks[n]->stop();
        }
    }
}
