#include "ChannelSocket.h"

#ifndef CHANNEL_SOCKET_SERVER_H
#define CHANNEL_SOCKET_SERVER_H

class ChannelSocketServer : public ChannelSocket
{
public:
    void init(void);
    void start(void);
    void tx(char *data, int size);
    void rx(char *data, int size, int *received);
    void stop(void);

protected:
private:
};

#endif
