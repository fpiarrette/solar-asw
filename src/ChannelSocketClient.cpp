#include "ChannelSocketClient.h"
#include "Logger.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Channel::Error ChannelSocketClient::init(void)
{
    /* client socket is created */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketClient::start(void)
{
    Channel::Error r;

    /* server address definition */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    /* change client socket to NON BLOCKING mode */
    if ((r = setNonBlock(fd)) != Channel::Error::E_OK)
    {
        return r;
    }
    else
    {
        return Channel::Error::E_OK;
    }
}

Channel::Error ChannelSocketClient::tx(char *data, int size, int *transmitted)
{
    if (fd > 0)
        return secureTx(fd, data, size, transmitted);
    else
        return Channel::Error::E_STA;
}

Channel::Error ChannelSocketClient::rx(char *data, int size, int *received)
{
    if (fd > 0)
        return secureRx(fd, data, size, received);
    else
        return Channel::Error::E_STA;
}

Channel::Error ChannelSocketClient::stop(void)
{
    if (fd > 0)
        return secureStop(fd);
    else
        return Channel::Error::E_STA;
}
