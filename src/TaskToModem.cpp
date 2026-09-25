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
    char b[512];
    int s = 0;

    source->rx(b, sizeof(b), &s);

    if (s > 0)
        fifo.push(b, s);

    return s > 0;
}

Scheduller::Task::Result TaskToModem::run(long int time)
{
    int t, r;
    char b[2 * 1024];

    /* check input */
    need(time);

    if (fifo.empty())
        return Scheduller::Task::Result::IDLE;

    L_DEBUG("fifo size %d: ", fifo.size());

    r = fifo.peek(b, sizeof(b));

    sink->tx(b, r, &t);

    L_DEBUG("tx %d: ", t);

    if (t > 0)
    {
        /* in case data sent is less than read */
        /* return data to buffer -> adjust read pointer */
        fifo.consume(t);
        L_DEBUG("consumed %d: ", t);
        L_DEBUG("fifo size %d: ", fifo.size());
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