#include "ChannelSocketServer.h"

#include <sys/socket.h>
#include <netinet/in.h>

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
}

void ChannelSocketServer::tx(char *data, int size)
{
}

void ChannelSocketServer::rx(char *data, int size, int *received)
{
    int clientSocket = accept(fd, nullptr, nullptr);
    /* FIXME is blocking */
    recv(fd, data, size, 0);
}

void ChannelSocketServer::stop(void)
{
    /* close(fd); */
}
