#include "ProcessFromModem.h"

#include <string.h>

void ProcessFromModem::init(void)
{
    channelSocketClient.init();
    channelSpi.init();
}

void ProcessFromModem::start(void)
{
    channelSocketClient.start();
    channelSpi.start();
    write = 0;
    timeBarrier = 0;
}

void ProcessFromModem::run(long int time)
{
    char b[256];
    int r;
    channelSpi.receive(b, sizeof(b), &r);
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
        channelSocketClient.send(buffer, write);
        write = 0;
        timeBarrier = time + timeDeliveryLimit;
    }
}

void ProcessFromModem::stop(void)
{
    channelSocketClient.stop();
    channelSpi.stop();
}

void ProcessFromModem::setTimeDeliveryLimit(int value)
{
    timeDeliveryLimit = value;
}

void ProcessFromModem::setBufferSizeLimit(int value)
{
    bufferSizeLimit = value;
}
