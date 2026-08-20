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
    /* protocol AF_NET -> IPv4, SOCK_STREAM -> TCP socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    /* bind to the address */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketServer::start(void)
{
    Channel::Error r;

    if (listen(fd, 5) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    /* Fixme check errors */
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

Channel::Error ChannelSocketServer::tx(char *data, int size)
{
    if (clientSocket > 0)
    {
        /* FIXME manage errors */
        send(clientSocket, data, size, 0);
    }
    else
    {
        checkClientConnection();
    }
    /* FIXME manage errors in a better way, unify the function send to be available for client and server */
    return Channel::Error::E_OK;
}

Channel::Error ChannelSocketServer::rx(char *data, int size, int *received)
{
    if (clientSocket > 0)
    {
        /* FIXME manage errors */
        return secureRx(clientSocket, data, size, received);
    }
    else
    {
        return checkClientConnection();
    }
}

Channel::Error ChannelSocketServer::stop(void)
{
    if (clientSocket > 0)
    {
        shutdown(clientSocket, SHUT_RDWR);
        close(clientSocket);
    }
    shutdown(fd, SHUT_RDWR);
    close(fd);
    /* reuse stop for client and server */
    return Channel::Error::E_OK;
}
