#include "TaskKiller.h"

#include "alarm_def.h"
#include "Alarms.h"
#include "Logger.h"

#include <string.h>

#define LOG_PREFIX "Task killer "

const char *TaskKiller::getName(void)
{
    return "Killer";
}

void TaskKiller::prepare(void)
{
    source->init();
    source->start();

    L_NOTICE(LOG_PREFIX "prepared");
}

Scheduller::Task::Result TaskKiller::run(long int time)
{
    char buffer[16];
    int size;

    memset(buffer, 0, sizeof(buffer));

    /* try to receive data */
    source->rx(buffer, sizeof(buffer) - 1, &size);

    if (size > 0)
    {
        /* trim string */
        buffer[strcspn(buffer, "\r\n")] = '\0';
    
        if ((strcmp("stop", buffer) == 0) || (strcmp("STOP", buffer) == 0))
        {
            Alarms::getInstance()->set(ALARM_DEF_STOP);
        }

        if ((strcmp("kill", buffer) == 0) || (strcmp("KILL", buffer) == 0))
        {
            Alarms::getInstance()->set(ALARM_DEF_KILL);
        }

        if ((strcmp("resume", buffer) == 0) || (strcmp("RESUME", buffer) == 0))
        {
            Alarms::getInstance()->set(ALARM_DEF_RESUME);
        }

        return Scheduller::Task::Result::WORKED;
    }

    return Scheduller::Task::Result::IDLE;
}

void TaskKiller::stop(void)
{
    if (source != NULL)
    {
        source->stop();
        source = NULL;
    }

    L_NOTICE(LOG_PREFIX "stopped");
}

void TaskKiller::setSource(Channel *s)
{
    source = s;
}
