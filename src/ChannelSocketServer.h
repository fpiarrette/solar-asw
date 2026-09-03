#include "ChannelSocket.h"

#ifndef CHANNEL_SOCKET_SERVER_H
#define CHANNEL_SOCKET_SERVER_H

class ChannelSocketServer : public ChannelSocket
{
public:
    ~ChannelSocketServer()
    {
        /* make sure that stop function is called */
        stop();
    }
    Channel::Error init(void);
    Channel::Error start(void);
    Channel::Error tx(char *data, int size, int *transmitted);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);

protected:
    Channel::Error checkClientConnection(void);
    int clientSocket;
private:
};

#endif
