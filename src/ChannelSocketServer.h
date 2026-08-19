#include "ChannelSocket.h"

#ifndef CHANNEL_SOCKET_SERVER_H
#define CHANNEL_SOCKET_SERVER_H

class ChannelSocketServer : public ChannelSocket
{
public:
    void init(void);
    void start(void);
    void send(char *data, int size);
    void receive(char *data, int size, int *received);
    void stop(void);
};

#endif
