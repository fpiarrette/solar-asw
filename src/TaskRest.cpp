#include "TaskRest.h"

#include "Alarms.h"
#include "alarm_def.h"
#include "Logger.h"

#define LOG_PREFIX "REST task "

const char *TaskRest::getName(void)
{
    return "REST task";
}

void TaskRest::prepare(void)
{
    /* expendedTime = 0; */

    L_NOTICE(LOG_PREFIX "prepared");
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
    L_NOTICE(LOG_PREFIX "stopped");
}
