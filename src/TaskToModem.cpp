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

int TaskToModem::need(long int time)
{
    /* try to receive data */
    source->rx(bufferRx, sizeof(bufferRx), &bufferRxSize);

    return bufferRxSize > 0;
}

Scheduller::Task::Result TaskToModem::run(long int time)
{
    int t, r;
    char b[2 * 1024];

    if (!need(time))
        return Scheduller::Task::Result::IDLE;

    circular.push(bufferRx, bufferRxSize);

    r = circular.peek(b, sizeof(b));

    sink->tx(b, r, &t);

    if (t > 0)
    {
        /* only transmitted data is consumed */
        circular.consume(t);
    }

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