#include "ChannelSocket.h"

#include "Logger.h"

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
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_INT;
    }
    return Channel::Error::E_OK;
}

Channel::Error ChannelSocket::secureRx(int f, Fifo<char> &fifo)
{
    int t;
    char b[fifo.capacity()];

    t = recv(f, b, sizeof(b), 0);
    if (t > 0)
    {
        L_DEBUG("received %d", t);
        fifo.push(b, t);
        return Channel::Error::E_OK;
    }
    else if (t == 0)
    {
        return Channel::Error::E_OK;
    }
    else
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return Channel::Error::E_OK;
        }
        else
        {
            LOGGER_DEBUG_ERRNO;

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

    if (r != 0)
    {
        if (errno == ENOTCONN)
        {
            /* not really an error */
            r = 0;
        }
        else
        {
            LOGGER_DEBUG_ERRNO;
        }
    }

    close(f);

    return r != 0 ? Channel::Error::E_INT : Channel::Error::E_OK;
}

Channel::Error ChannelSocket::secureTx(int f, Fifo<char> &fifo)
{
    int r;
    char b[fifo.size()];

    fifo.peek(b, sizeof(b));

    r = send(f, b, sizeof(b), 0);

    L_DEBUG("sent %d from %d", r, fifo.size());

    if (r == (int)sizeof(b))
    {
        fifo.consume(r);
        return Channel::Error::E_OK;
    }
    else if (r >= 0 && r < (int)sizeof(b))
    {
        fifo.consume(r);
        return Channel::Error::E_TRY;
    }
    else if (r < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return Channel::Error::E_TRY;
        }
        else
        {
            LOGGER_DEBUG_ERRNO;

            return Channel::Error::E_INT;
        }
    }
    else
    {
        return Channel::Error::E_INT;
    }
}

Channel::Error ChannelSocket::setPort(int p)
{
    port = p;
    return Channel::Error::E_OK;
}
