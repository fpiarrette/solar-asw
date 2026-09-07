#include "Scheduller.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"
#include "Signals.h"
#include "utils.h"

#include <string.h>

Scheduller::Scheduller()
{
    nextTask = -1;

    memset(tasks, 0, sizeof(tasks));

    period = 50;
}

void Scheduller::addTask(Scheduller::Task *task, int executionOrder)
{
    tasks[executionOrder] = task;

    L_DEBUG("'%s' added", task->getName());
}

void Scheduller::run(void)
{
    long int cycleStartTime, elapsedTime, sleepTime;
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

    globalStartTime = utils_curr_time_in_ms();

    /* align time alarms */
    publishTimeAlarms(globalStartTime);
    Alarms::getInstance()->clearAll();
    terminated = 0;
    paused = 0;

    /* scheduller main loop */
    while (!terminated)
    {
        if (!paused)
        {
            /* get start time in ms */
            cycleStartTime = utils_curr_time_in_ms() - globalStartTime;

            publishTimeAlarms(cycleStartTime);

            for (n = 0; n < SCHEDULLER_SIZE; n++)
            {
                if (tasks[n] != NULL && (tasks[n]->run(cycleStartTime) == Scheduller::Task::Result::WORKED))
                {
                    /* Task::run return != 0 when work is performed, in that case Scheduller shall STOP */
                    /* searching for a task to execute */
                    break;
                }
            }

            elapsedTime = utils_curr_time_in_ms() - cycleStartTime - globalStartTime;
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

        if (Alarms::getInstance()->get(ALARM_DEF_STOP))
        {
            paused = 1;
            Alarms::getInstance()->clear(ALARM_DEF_STOP);
        }

        if (Alarms::getInstance()->get(ALARM_DEF_KILL))
        {
            terminated = 1;
            Alarms::getInstance()->clear(ALARM_DEF_KILL);
        }

        if (Alarms::getInstance()->get(ALARM_DEF_RESUME))
        {
            paused = 0;
            Alarms::getInstance()->clear(ALARM_DEF_RESUME);
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

void Scheduller::publishTimeAlarms(long int time)
{
    long int t, s, h;

    t = time / 10000;
    s = time / 1000;
    h = time / 100;

    if (t != previousTenthSecondCounter)
    {
        Alarms::getInstance()->set(ALARM_DEF_TENTH_SECOND);
        previousTenthSecondCounter = t;
    }

    if (s != previousSecondCounter)
    {
        Alarms::getInstance()->set(ALARM_DEF_SECOND);
        previousSecondCounter = s;
    }

    if (h != previousHundredMiliSeconds)
    {
        Alarms::getInstance()->set(ALARM_DEF_HUNDRED_MS);
        previousHundredMiliSeconds = h;
    }
}

int Scheduller::hasMoreTasks(void)
{
    if (nextTask == -1)
        nextTask = 0;
    else
        nextTask++;

    while ((tasks[nextTask] == NULL) && nextTask < SCHEDULLER_SIZE)
        nextTask++;

    if (nextTask < SCHEDULLER_SIZE)
    {
        return 1;
    }
    else
    {
        nextTask = -1;
        return 0;
    }
}

Scheduller::Task *Scheduller::getNextTask(void)
{
    return tasks[nextTask];
}
