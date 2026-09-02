#include "TaskToModem.h"

#include "Logger.h"

#include <string.h>

const char *TaskToModem::getName(void)
{
    return "Communication task from EGSE -> MODEM";
}

void TaskToModem::prepare(void)
{
    expendedTime = 0;

    source->init();
    sink->init();

    source->start();
    sink->start();

    L_DEBUG("prepared");
}

int TaskToModem::need(long int time)
{
    /* try to receive data */
    source->rx(bufferRx, sizeof(bufferRx), &bufferRxSize);

    return bufferRxSize > 0;
}

void TaskToModem::run(long int time)
{
    int t, r;
    char b[2 * 1024];

    storage.write(bufferRx, bufferRxSize);

    storage.read(b, sizeof(b), &r);

    sink->tx(b, r, &t);

    if (t < r)
    {
        /* in case data sent is less than read */
        /* return data to buffer -> adjust read pointer */
        storage.rewind(r - t);
    }
}

void TaskToModem::stop(void)
{
    source->stop();
    sink->stop();

    L_DEBUG("stopped");
}

void TaskToModem::setSource(Channel *s)
{
    source = s;
}

void TaskToModem::setSink(Channel *s)
{
    sink = s;
}