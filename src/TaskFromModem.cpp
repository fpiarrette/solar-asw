#include "TaskFromModem.h"

#include "Logger.h"

#include <string.h>

#define LOG_PREFIX "Task from modem "

const char *TaskFromModem::getName(void)
{
    return "MODEM -> EGSE";
}

void TaskFromModem::prepare(void)
{
    /* expendedTime = 0; */

    source->start();
    sink->start();

    timeBarrier = 0;

    timeDeliveryLimit = 1000;

    L_NOTICE(LOG_PREFIX "prepared, time limit %d ms, size limit %d bytes", timeDeliveryLimit, sizeLimit);
}

int TaskFromModem::need(long int time)
{
    char b[512];
    int s;

    /* try to receive */
    source->rx(b, sizeof(b), &s);

    if (s > 0)
    {
        fifo.push(b, s);
    }

    /* return 1 only in case data is received */
    return s > 0;
}

Scheduller::Task::Result TaskFromModem::run(long int time)
{
    need(time);

    if (fifo.empty())
        return Scheduller::Task::IDLE;

    /* send packet in case amount of bytes are sufficient */
    if ((int) fifo.size() > sizeLimit)
    {
        L_DEBUG("sent because of size limit");

        forwardToSink(time);
    }
    else if (timeBarrier < time)
    {
        L_DEBUG("sent because of time limit");

        forwardToSink(time);
    }

    return Scheduller::Task::Result::WORKED;
}

void TaskFromModem::forwardToSink(long int time)
{
    int t;
    int r;
    char b[2 * 1024];

    r = fifo.peek(b, sizeof(b));

    sink->tx(b, r, &t);

    if (t > 0)
    {
        fifo.consume(t);
    }

    timeBarrier = time + timeDeliveryLimit;
}

void TaskFromModem::stop(void)
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

void TaskFromModem::setTimeDeliveryLimit(int value)
{
    timeDeliveryLimit = value;
}

void TaskFromModem::setSizeLimit(int value)
{
    sizeLimit = value;
}

void TaskFromModem::setSource(Channel *s)
{
    source = s;
}

void TaskFromModem::setSink(Channel *s)
{
    sink = s;
}