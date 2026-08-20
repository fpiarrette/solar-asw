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

Channel::Error ChannelSocket::secureStop(int f)
{
    int r;

    if (f < 0)
    {
        return Channel::Error::E_ARG;
    }

    r = shutdown(f, SHUT_RDWR);

    if (errno == ENOTCONN)
    {
        /* not really an error */
        r = 0;
    }

    close(f);

    return r != 0 ? Channel::Error::E_INT : Channel::Error::E_OK;
}

Channel::Error ChannelSocket::secureTx(int f, char *data, int size, int *transmitted)
{
    int r;

    r = send(f, data, size, 0);

    if (r == size)
    {
        /* block fully sent */
        return Channel::Error::E_OK;
    }
    else if (r >= 0 && r < size)
    {
        *transmitted = r;
        return Channel::Error::E_TRY;
    }
    else if (r < 0)
    {
        *transmitted = 0;
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
        *transmitted = 0;
        return Channel::Error::E_INT;
    }
}
