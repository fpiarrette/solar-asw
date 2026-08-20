#include "ChannelSocket.h"

#ifndef CHANNEL_SOCKET_CLIENT_H
#define CHANNEL_SOCKET_CLIENT_H

class ChannelSocketClient : public ChannelSocket
{
public:
    Channel::Error init(void);
    Channel::Error start(void);
    Channel::Error tx(char *data, int size);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);

protected:
private:
};

#endif
