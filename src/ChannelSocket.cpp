#include "ChannelSocket.h"

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Channel::Error ChannelSocket::setNonBlock(int f)
{
    int c, r;
    c = fcntl(f, F_GETFL);
    c |= O_NONBLOCK;
    r = fcntl(f, F_SETFL, c);
    if (r != 0)
    {
        return Channel::Error::E_INT;
    }
    return Channel::Error::E_OK;
}

Channel::Error ChannelSocket::secureRx(int f, void *b, int s, int *r)
{

    int t;

    t = recv(f, b, s, 0);
    if (t > 0)
    {
        *r = t;
        return Channel::Error::E_OK;
    }
    else if (t == 0)
    {
        *r = 0;
        return Channel::Error::E_OK;
    }
    else
    {
        *r = 0;
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return Channel::Error::E_OK;
        }
        else
        {
            return Channel::Error::E_INT;
        }
    }
}