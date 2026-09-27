#include "TaskKiller.h"

#include "Alarms.h"
#include "Logger.h"
#include "setup.h"

#include <string.h>

#define LOG_PREFIX "Task killer "

const char *TaskKiller::getName(void)
{
    return "Killer";
}

void TaskKiller::prepare(void)
{
    source->start();

    L_NOTICE(LOG_PREFIX "prepared");
}

Scheduller::Task::Result TaskKiller::run(long int time)
{
    Fifo<char> fifo(256);

    /* try to receive data */
    source->rx(fifo);

    if (fifo.size() > 0)
    {
        char buffer[fifo.size()];
        fifo.pop(buffer, sizeof(buffer));

        /* trim string */
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if ((strcmp("stop", buffer) == 0) || (strcmp("STOP", buffer) == 0))
        {
            Alarms::getInstance()->set(SETUP_ALARM_STOP);
        }

        if ((strcmp("kill", buffer) == 0) || (strcmp("KILL", buffer) == 0))
        {
            Alarms::getInstance()->set(SETUP_ALARM_KILL);
        }

        if ((strcmp("resume", buffer) == 0) || (strcmp("RESUME", buffer) == 0))
        {
            Alarms::getInstance()->set(SETUP_ALARM_RESUME);
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
