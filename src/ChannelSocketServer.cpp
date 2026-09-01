#include "ChannelSocketServer.h"
#include "Logger.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

Channel::Error ChannelSocketServer::init(void)
{
    int port = 9000;
    /* protocol AF_NET -> IPv4, SOCK_STREAM -> TCP socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    L_DEBUG("server socket file descriptor %d", fd);

    /* bind to the address */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    L_DEBUG("server socket bound to %d", port);

    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketServer::start(void)
{
    Channel::Error r;

    L_DEBUG("starting");

    if (listen(fd, 5) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    L_DEBUG("server socket is listening...");

    if ((r = setNonBlock(fd)) != Channel::Error::E_OK)
    {
        return r;
    }
    /* fix value of client socket */
    clientSocket = -1;

    /* try to accept a client connection */
    r = checkClientConnection();

    return r == Channel::Error::E_OK || r == Channel::Error::E_TRY ? Channel::Error::E_OK : r;
}

Channel::Error ChannelSocketServer::checkClientConnection(void)
{
    if (clientSocket < 0)
    {
        clientSocket = accept(fd, nullptr, nullptr);
        if (clientSocket > 0)
        {
            L_DEBUG("client socket accepted on %d", clientSocket);
            /* set client socket NON BLOCKING */
            return setNonBlock(clientSocket);
        }
        else if (clientSocket < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                return Channel::Error::E_TRY;
            }
            else
            {
                return Channel::Error::E_INT;
            }
        }
        else
        {
            /* should no happend, fd 0 should be already used */
            return Channel::Error::E_INT;
        }
    }
    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketServer::tx(char *data, int size, int *transmitted)
{
    if (clientSocket > 0)
    {
        return secureTx(clientSocket, data, size, transmitted);
    }
    else
    {
        return checkClientConnection();
    }
}

Channel::Error ChannelSocketServer::rx(char *data, int size, int *received)
{
    if (clientSocket > 0)
    {
        return secureRx(clientSocket, data, size, received);
    }
    else
    {
        return checkClientConnection();
    }
}

Channel::Error ChannelSocketServer::stop(void)
{
    Channel::Error r1 = Channel::Error::E_OK;
    Channel::Error r2 = Channel::Error::E_OK;

    if (clientSocket > 0)
        r1 = secureStop(clientSocket);

    if (fd > 0)
        r2 = secureStop(fd);

    return r1 == Channel::Error::E_OK && r2 == Channel::Error::E_OK ? Channel::Error::E_OK : Channel::Error::E_INT;
}
