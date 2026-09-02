#include "TaskRest.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

const char *TaskRest::getName(void)
{
    return "REST task";
}

void TaskRest::prepare(void)
{
    /* expendedTime = 0; */

    L_DEBUG("prepared");
}

int TaskRest::need(long int time)
{
    return 0;
}

void TaskRest::run(long int time)
{
}

void TaskRest::stop(void)
{
    L_DEBUG("stopped");
}
