#include "ChannelSpiSlave.h"

#include "Logger.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

#define LOG_PREFIX "Channel SPI slave "

ChannelSpiSlave::ChannelSpiSlave(void)
{
    memset(deviceName, 0, sizeof(deviceName));
    memset(transmisionBuffer, 0, sizeof(transmisionBuffer));
    transmisionDataSize = 0;

    fd = -1;
}

Channel::Error ChannelSpiSlave::start(void)
{
    if (fd > 0)
    {
        L_ERROR("incorrect state");

        return Channel::Error::E_STA;
    }

    if (strlen(deviceName) == 0)
    {

        L_ERROR("device name not configured");

        return Channel::Error::E_STA;
    }

    fd = open(deviceName, O_RDWR);

    if (fd < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_INT;
    }

    L_NOTICE(LOG_PREFIX "device %s initialized: fd %d", deviceName, fd);

    L_NOTICE(LOG_PREFIX "started");

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpiSlave::tx(char *data, int size, int *tranmitted)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpiSlave::rx(char *data, int size, int *received)
{
    return Channel::Error::E_OK;
}

Channel::Error ChannelSpiSlave::stop(void)
{
    if (fd > 0)
    {
        close(fd);
        fd = -1;
        L_NOTICE(LOG_PREFIX "stopped");
        return Channel::Error::E_OK;
    }
    else
    {
        L_WARNING(LOG_PREFIX "incorrect state");

        return Channel::Error::E_STA;
    }
}
