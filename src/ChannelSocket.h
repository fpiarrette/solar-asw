#include "Channel.h"

#ifndef CHANNEL_SOCKET_H
#define CHANNEL_SOCKET_H

class ChannelSocket : public Channel
{
public:
    void init(void *data);
    void start(void *data);
    void send(char *data, int size);
    void receive(char *data, int *size);
    void stop(void *data);
};

#endif
