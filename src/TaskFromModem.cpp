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

    source->init();
    sink->init();

    source->start();
    sink->start();

    bufferRxSize = 0;
    timeBarrier = 0;

    timeDeliveryLimit = 1000;

    L_NOTICE(LOG_PREFIX "prepared, time limit %d ms, size limit %d bytes", timeDeliveryLimit, bufferRxSize);
}

int TaskFromModem::need(long int time)
{
    /* try to receive */
    source->rx(bufferRx, sizeof(bufferRx), &bufferRxSize);

    /* return 1 only in case data is received */
    return bufferRxSize > 0;
}

Scheduller::Task::Result TaskFromModem::run(long int time)
{
    if (!need(time))
        return Scheduller::Task::IDLE;

    /* update write pointer*/
    bufferStorage.write(bufferRx, bufferRxSize);

    /* send packet in case amount of bytes are sufficient */
    if (bufferStorage.getAvailable() > sizeLimit)
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

    bufferStorage.read(b, sizeof(b), &r);
    sink->tx(b, r, &t);

    if (t < r)
    {
        /* in case data sent is less than read */
        /* return data to buffer -> adjust read pointer */
        bufferStorage.rewind(r - t);
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