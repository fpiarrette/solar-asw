#include "ChannelSpi.h"

#ifndef CHANNEL_SPI_MASTER_H
#define CHANNEL_SPI_MASTER_H

class ChannelSpiMaster : public ChannelSpi
{
public:
    ChannelSpiMaster();
    ~ChannelSpiMaster()
    {
        /* make sure that stop function is called */
        stop();
    }

    Channel::Error start(void);
    Channel::Error tx(char *data, int size, int *transmitted);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);

protected:
    void dumpStatus(void);
    int getMode(void);

private:
    char receptionBuffer[512];
    int receivedDataSize;
};

#endif
