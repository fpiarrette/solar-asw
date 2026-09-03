#include "ChannelSocketClient.h"
#include "Logger.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define LOG_PREFIX "Channel TCP client "

Channel::Error ChannelSocketClient::init(void)
{
    /* client socket is created */
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    L_NOTICE(LOG_PREFIX "client socket file descriptor %d", fd);

    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketClient::start(void)
{
    Channel::Error r;

    L_NOTICE(LOG_PREFIX "trying to connect to %s:%d...", ipAddress, port);

    /* server address definition */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress, &serverAddress.sin_addr);

    if (connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_TRY;
    }

    L_NOTICE(LOG_PREFIX "client connected to server");

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

Channel::Error ChannelSocketClient::setIpAddress(const char *a)
{
    if (a == NULL)
        return Channel::Error::E_ARG;

    if ((strlen(a) + 1) > IP_ADDRESS_SIZE)
        return Channel::Error::E_ARG;

    strncpy(ipAddress, a, IP_ADDRESS_SIZE);

    return Channel::Error::E_OK;
}
