#include "ChannelSpi.h"

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

#define LOG_PREFIX "Channel SPI "

ChannelSpi::ChannelSpi(void)
{
    memset(deviceName, 0, sizeof(deviceName));
    memset(receptionBuffer, 0, sizeof(receptionBuffer));
    receivedDataSize = 0;

    fd = -1;
}

Channel::Error ChannelSpi::init(void)
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

    return Channel::Error::E_OK;
}

void ChannelSpi::setDeviceName(const char *name)
{
    strncpy(deviceName, name, sizeof(deviceName));
}

void ChannelSpi::dumpStatus(void)
{
    __u8 lsb, bits;
    __u32 mode, speed;

    if (ioctl(fd, SPI_IOC_RD_MODE32, &mode) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return;
    }

    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return;
    }

    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return;
    }

    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return;
    }

    L_DEBUG("%s: spi mode 0x%x, %d bits %sper word, %u Hz max", deviceName, mode, bits, lsb ? "(lsb first) " : "", speed);
}

Channel::Error ChannelSpi::start(void)
{
    /* dump SPI dev status */
    dumpStatus();

    L_NOTICE(LOG_PREFIX "started");

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::tx(char *data, int size, int *tranmitted)
{
    receivedDataSize = 0;

    /* dummy transmision */
    strncpy(receptionBuffer, data, sizeof(receptionBuffer));
    receivedDataSize = size;

    *tranmitted = size;

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::rx(char *data, int size, int *received)
{
    *received = receivedDataSize;

    if (receivedDataSize > 0)
    {
        memcpy(data, receptionBuffer, receivedDataSize < size ? receivedDataSize : size);

        receivedDataSize = 0;
    }

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpi::stop(void)
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
