#include "Channel.h"

#ifndef CHANNEL_SPI_H
#define CHANNEL_SPI_H

class ChannelSpi : public Channel
{
public:
    ChannelSpi();
    ~ChannelSpi()
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
    char receptionBuffer[512];
    int receivedDataSize;
};

#endif
