#include "TaskIdle.h"

#include "Logger.h"

const char *TaskIdle::getName(void)
{
    return "Idle task";
}

void TaskIdle::prepare(void)
{
    expendedTime = 0;

    period = 1000;
    nextExecution = 0;

    L_DEBUG("prepared, running at %d ms", period);
}

int TaskIdle::need(long int time)
{
    /* needs to be executed if nextExecution is in the past */
    return nextExecution < time;
}

void TaskIdle::run(long int time)
{
    L_DEBUG("idle...., next execution time %d ms", nextExecution);
    nextExecution = time + period;
}

void TaskIdle::stop(void)
{
    L_DEBUG("stopped");
}
