#include "ChannelSpi.h"

#ifndef CHANNEL_SPI_SLAVE_H
#define CHANNEL_SPI_SLAVE_H

class ChannelSpiSlave : public ChannelSpi
{
public:
    ChannelSpiSlave();
    ~ChannelSpiSlave()
    {
        /* make sure that stop function is called */
        stop();
    }

    Channel::Error start(void);
    Channel::Error tx(Fifo<char>&f);
    Channel::Error rx(Fifo<char>&f);
    Channel::Error stop(void);

protected:
private:
    char transmisionBuffer[512];
    int transmisionDataSize;
};

#endif
