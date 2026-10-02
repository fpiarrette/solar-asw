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

Scheduller::Task::Result TaskFromModem::run(long int time)
{
    /* try to receive */
    source->rx(fifo);

    if (fifo.empty())
        return Scheduller::Task::IDLE;

    /* send packet in case amount of bytes are sufficient */
    if ((int)fifo.size() > sizeLimit)
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
    sink->tx(fifo);

    timeBarrier = time + timeDeliveryLimit;
}

void TaskFromModem::stop(void)
{
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