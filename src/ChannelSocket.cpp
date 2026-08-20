#include "ChannelSocket.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int ChannelSocket::setNonBlock(int f)
{
    int c, r;
    c = fcntl(f, F_GETFL);
    c |= O_NONBLOCK;
    r = fcntl(f, F_SETFL, c);
    if (r != 0)
    {
        return CHANNEL_E_INT;
    }
    return CHANNEL_E_OK;
}

int ChannelSocket::secureRx(int f, void *b, int s, int *r)
{

    int t;

    t = recv(f, b, s, 0);
    if (t > 0)
    {
        *r = t;
        return CHANNEL_E_OK;
    }
    else if (t == 0)
    {
        *r = 0;
        return CHANNEL_E_OK;
    }
    else
    {
        *r = 0;
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return CHANNEL_E_OK;
        }
        else
        {
            return CHANNEL_E_INT;
        }
    }
}