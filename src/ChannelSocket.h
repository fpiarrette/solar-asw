#include "Channel.h"

#ifndef CHANNEL_SOCKET_H
#define CHANNEL_SOCKET_H

class ChannelSocket : public Channel
{
public:
protected:
    int setNonBlock(int fd);
    int secureRx(int f, void *b, int s, int *r);
    int fd;

private:
};

#endif
