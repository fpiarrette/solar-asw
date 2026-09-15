#include "Channel.h"

#ifndef CHANNEL_SPI_SLAVE_H
#define CHANNEL_SPI_SLAVE_H

class ChannelSpiSlave : public Channel
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

    void setDeviceName(const char *name);

protected:
    void dumpStatus(void);

private:
    int fd;
    char deviceName[256];
    char transmisionBuffer[512];
    int transmisionDataSize;
};

#endif
