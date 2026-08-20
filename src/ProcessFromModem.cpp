#include "ProcessFromModem.h"

#include <string.h>

void ProcessFromModem::init(Context *context)
{
    context->getSource()->init();
    context->getSink()->init();
}

void ProcessFromModem::start(Context *context)
{
    context->getSource()->start();
    context->getSink()->start();
    write = 0;
    timeBarrier = 0;
}

void ProcessFromModem::run(Context *context, long int time)
{
    char b[256];
    int r, t;
    context->getSource()->rx(b, sizeof(b), &r);
    int sendPacket = 0;

    if (r > 0)
    {
        memcpy(&buffer[write], b, r);
        write += r;
        /* send packet in case amount of bytes are sufficient */
        if (write > bufferSizeLimit)
        {
            sendPacket = 1;
        }
    }

    /* send packet even when there is no enough bytes in case time barrier is reached */
    if ((sendPacket == 1) || ((write > 0) && (timeBarrier < time)))
    {
        /* FIXME manage retries */
        context->getSink()->tx(buffer, write, &t);
        write = 0;
        timeBarrier = time + timeDeliveryLimit;
    }
}

void ProcessFromModem::stop(Context *context)
{
    context->getSource()->stop();
    context->getSink()->stop();
}

void ProcessFromModem::setTimeDeliveryLimit(int value)
{
    timeDeliveryLimit = value;
}

void ProcessFromModem::setBufferSizeLimit(int value)
{
    bufferSizeLimit = value;
}
