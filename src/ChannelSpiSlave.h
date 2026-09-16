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
    Channel::Error init(void);
    Channel::Error start(void);
    Channel::Error tx(char *data, int size, int *transmitted);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);

protected:
private:
    char transmisionBuffer[512];
    int transmisionDataSize;
};

#endif
