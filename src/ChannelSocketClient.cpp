#include "ChannelSocketClient.h"

#include <sys/socket.h>
#include <netinet/in.h>

void ChannelSocketClient::init(void)
{
    /* socket is created */
    fd = socket(AF_INET, SOCK_STREAM, 0);
}

void ChannelSocketClient::start(void)
{
    /* server address definition */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
}

void ChannelSocketClient::tx(char *data, int size)
{
    /* send(fd, data, size, 0); */
}

void ChannelSocketClient::rx(char *data, int size, int *received)
{
}

void ChannelSocketClient::stop(void)
{
}
