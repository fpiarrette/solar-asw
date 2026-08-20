#include "Channel.h"

#ifndef CHANNEL_SOCKET_H
#define CHANNEL_SOCKET_H

class ChannelSocket : public Channel
{
public:
protected:
    Channel::Error setNonBlock(int fd);
    Channel::Error secureRx(int f, void *b, int s, int *r);
    Channel::Error secureStop(int f);
    Channel::Error secureTx(int f, char *data, int size, int *transmitted);
    int fd;

private:
};

#endif
