#include "ChannelSocketServer.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void ChannelSocketServer::init(void)
{
    /* protocol AF_NET -> IPv4, SOCK_STREAM -> TCP socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    /* bind to the address */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
}

void ChannelSocketServer::start(void)
{
    listen(fd, 5);
    /* Fixme check errors */
    setNonBlock(fd);
    clientSocket = -1;
    checkClientConnection();
}

int ChannelSocketServer::checkClientConnection(void)
{
    if (clientSocket < 0)
    {
        clientSocket = accept(fd, nullptr, nullptr);
        if (clientSocket > 0)
        {
            /* set client socket NON BLOCKING */
            setNonBlock(clientSocket);
            return CHANNEL_E_OK;
        }
        else if (clientSocket < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                return CHANNEL_E_OK;
            }
            else
            {
                return CHANNEL_E_INT;
            }
        }
        else
        {
            /* should no happend, fd 0 should be already used */
            return CHANNEL_E_INT;
        }
    }
    return CHANNEL_E_OK;
}

void ChannelSocketServer::tx(char *data, int size)
{

    if (clientSocket > 0)
    {
        /* FIXME manage errors */
        send(clientSocket, data, size, 0);
    }
    else
    {
        checkClientConnection();
        /* return CHANNEL_E_OK; */
    }
}

void ChannelSocketServer::rx(char *data, int size, int *received)
{

    if (clientSocket > 0)
    {
        /* FIXME manage errors */
        secureRx(clientSocket, data, size, received);
    }
    else
    {
        checkClientConnection();
        /* return CHANNEL_E_OK; */
    }
}

void ChannelSocketServer::stop(void)
{
    if (clientSocket > 0)
    {
        shutdown(clientSocket, SHUT_RDWR);
        close(clientSocket);
    }
    shutdown(fd, SHUT_RDWR);
    close(fd);
}
