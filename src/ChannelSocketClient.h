#include "ChannelSocket.h"

#ifndef CHANNEL_SOCKET_CLIENT_H
#define CHANNEL_SOCKET_CLIENT_H

#define IP_NUM_SIZE (3)
#define IP_DOT_SIZE (1)
#define IP_NULL_TERMINATION_SIZE (1)
#define IP_ADDRESS_SIZE (IP_NUM_SIZE * 4 + IP_DOT_SIZE * 3 + IP_NULL_TERMINATION_SIZE)

class ChannelSocketClient : public ChannelSocket
{
public:
    ~ChannelSocketClient()
    {
        /* make sure that stop function is called */
        stop();
    }
    Channel::Error init(void);
    Channel::Error start(void);
    Channel::Error tx(char *data, int size, int *transmitted);
    Channel::Error rx(char *data, int size, int *received);
    Channel::Error stop(void);
    Channel::Error setIpAddress(const char *a);

protected:
private:
    char ipAddress[IP_ADDRESS_SIZE];
};

#endif
