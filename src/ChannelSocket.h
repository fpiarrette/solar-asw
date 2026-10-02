#include "Channel.h"

#ifndef CHANNEL_SOCKET_H
#define CHANNEL_SOCKET_H

class ChannelSocket : public Channel
{
public:
    ChannelSocket()
    {
        fd = -1;
    }
    Channel::Error setPort(int p);

protected:
    Channel::Error setNonBlock(int fd);
    Channel::Error secureRx(int f, Fifo<char> &fifo);
    Channel::Error secureStop(int f);
    Channel::Error secureTx(int f, Fifo<char> &fifo);
    int fd;
    int port;

private:
};

#endif
