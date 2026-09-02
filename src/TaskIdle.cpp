#include "TaskIdle.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

const char *TaskIdle::getName(void)
{
    return "Idle task";
}

void TaskIdle::prepare(void)
{
    /* expendedTime = 0; */

    L_DEBUG("prepared");
}

int TaskIdle::need(long int time)
{
    return Alarms::getInstance()->get(ALARM_DEF_SECOND);
}

void TaskIdle::run(long int time)
{
    Scheduller::Task *t;

    Alarms::getInstance()->clear(ALARM_DEF_SECOND);

    if (time == 0)
    {
        /* it has no sense to compute first cycle as time 0 will produce 'division by zero' */
        return;
    }

    L_DEBUG("Scheduller report, total time %d", time);

    while (scheduller->hasMoreTasks())
    {
        t = scheduller->getNextTask();
        L_DEBUG("%s,\texpended %d ms,\tcpu used %0.03f %%", t->getName(), t->getExpendedTime(), (float)t->getExpendedTime() / time);
    }
}

void TaskIdle::stop(void)
{
    L_DEBUG("stopped");
}
