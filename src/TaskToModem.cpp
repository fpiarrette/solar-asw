#include "TaskToModem.h"

#include "Logger.h"

#include <string.h>

#define LOG_PREFIX "Task to modem "

const char *TaskToModem::getName(void)
{
    return "EGSE -> MODEM";
}

void TaskToModem::prepare(void)
{
    source->start();
    sink->start();

    L_NOTICE(LOG_PREFIX "prepared");
}

Scheduller::Task::Result TaskToModem::run(long int time)
{
    /* check input */
    source->rx(fifo);

    if (fifo.empty())
        return Scheduller::Task::Result::IDLE;

    L_DEBUG("fifo size %d: ", fifo.size());

    sink->tx(fifo);

    L_DEBUG("fifo size %d: ", fifo.size());

    return Scheduller::Task::Result::WORKED;
}

void TaskToModem::stop(void)
{
    if (source != NULL)
    {
        source->stop();
        source = NULL;
    }

    if (sink != NULL)
    {
        sink->stop();
        sink = NULL;
    }

    L_NOTICE(LOG_PREFIX "stopped");
}

void TaskToModem::setSource(Channel *s)
{
    source = s;
}

void TaskToModem::setSink(Channel *s)
{
    sink = s;
}