#include "ChannelSocketClient.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void ChannelSocketClient::init(void)
{
    /* client socket is created */
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
    /* change client socket to NON BLOCKING mode */
    if (setNonBlock(fd) != CHANNEL_E_OK) {
        /* FIXME manage error */
    }
}

void ChannelSocketClient::tx(char *data, int size)
{
    send(fd, data, size, 0);
}

void ChannelSocketClient::rx(char *data, int size, int *received)
{
    /* FIXME manage erros */
    secureRx(fd, data, size, received);
}

void ChannelSocketClient::stop(void)
{
    shutdown(fd, SHUT_RDWR);
    close(fd);
}
