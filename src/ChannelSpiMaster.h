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
    Channel::Error tx(Fifo<char> &f);
    Channel::Error rx(Fifo<char> &f);
    Channel::Error stop(void);

protected:
    void dumpStatus(void);
    int getMode(void);

private:
    Fifo<char> reception;
};

#endif
