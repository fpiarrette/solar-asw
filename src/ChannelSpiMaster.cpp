#include "ChannelSpiMaster.h"

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

#define LOG_PREFIX "Channel SPI master "

ChannelSpiMaster::ChannelSpiMaster(void)
{
    memset(deviceName, 0, sizeof(deviceName));
    memset(receptionBuffer, 0, sizeof(receptionBuffer));
    receivedDataSize = 0;

    fd = -1;

    /* CPOL (Clock Polarity): nivel del reloj cuando está inactivo. */
    /* 0: reloj en reposo a nivel bajo. */
    /* 1: reloj en reposo a nivel alto. */
    /* CPHA (Clock Phase): en qué flanco se muestrean los datos. */
    /* 0: se leen en el primer flanco. */
    /* 1: se leen en el segundo flanco. */
    clockPolarity = 0;
    clockPhase = 0;
    /* 8 bits */
    bits = 8;
    /* 1MHz */
    speed = 1000000;
}

void ChannelSpiMaster::dumpStatus(void)
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

Channel::Error ChannelSpiMaster::start(void)
{
    int mode;

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

    if (fd < 0)
    {
        return Channel::Error::E_STA;
    }

    /* build PSI mode from clockPolarity and clockPhase */
    mode = getMode();

    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_INT;
    }

    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_INT;
    }

    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
    {
        LOGGER_DEBUG_ERRNO;

        return Channel::Error::E_INT;
    }

    /* dump SPI dev status */
    dumpStatus();

    L_NOTICE(LOG_PREFIX "started");

    return Channel::Error::E_OK;
}

Channel::Error ChannelSpiMaster::tx(char *data, int size, int *tranmitted)
{
    struct spi_ioc_transfer transfer;
    int dataToTransmit;

    receivedDataSize = 0;
    *tranmitted = 0;

    if ((unsigned int)size > sizeof(receptionBuffer))
    {
        dataToTransmit = sizeof(receptionBuffer);
    }
    else
    {
        dataToTransmit = size;
    }

    memset(&transfer, 0, sizeof(transfer));
    transfer.tx_buf = (unsigned long long)data;
    transfer.rx_buf = (unsigned long long)receptionBuffer;
    /* same amount of data for tx and rx */
    transfer.len = dataToTransmit;

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &transfer) < 0)
    {
        LOGGER_DEBUG_ERRNO;
        return Channel::Error::E_INT;
    }

    /* data comes in at same rate than data goes out */
    receivedDataSize = dataToTransmit;

    /* ioctl do not fail, so is addumed that data is transmited */
    *tranmitted = dataToTransmit;

    if (dataToTransmit < size)
    {
        /* in case transmitter data is less than original size */
        return Channel::Error::E_TRY;
    }
    else
    {
        /* in case than whole data is fully sent */
        return Channel::Error::E_OK;
    }
}

Channel::Error ChannelSpiMaster::rx(char *data, int size, int *received)
{

    if (receivedDataSize > 0)
    {
        if (size > receivedDataSize)
        {
            size = receivedDataSize;
        }

        memcpy(data, receptionBuffer, size);

        receivedDataSize -= size;

        *received = size;

        if (receivedDataSize > 0)
            return Channel::Error::E_TRY;
        else
            return Channel::Error::E_OK;
    }
    else
    {
        *received = 0;
        return Channel::Error::E_OK;
    }
}

Channel::Error ChannelSpiMaster::stop(void)
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

int ChannelSpiMaster::getMode(void)
{

    if (clockPolarity == 0 && clockPhase == 0)
    {
        return SPI_MODE_0;
    }
    else if (clockPolarity == 0 && clockPhase != 0)
    {
        return SPI_MODE_1;
    }
    else if (clockPolarity != 0 && clockPhase == 0)
    {
        return SPI_MODE_2;
    }
    else
    {
        return SPI_MODE_3;
    }
}
