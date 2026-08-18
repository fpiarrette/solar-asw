#include "Channel.h"

#ifndef CHANNEL_SOCKET_H
#define CHANNEL_SOCKET_H

class ChannelSocket : public Channel
{
public:
    void init(void);
    void start(void);
    void send(char *data, int size);
    void receive(char *data, int size, int *received);
    void stop(void);
};

#endif
