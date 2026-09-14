
#include "test_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

int dump_status(int fd)
{
    __u8 lsb, bits;
    __u32 mode, speed;

    if (ioctl(fd, SPI_IOC_RD_MODE32, &mode) < 0)
    {
        perror("ioctl SPI_IOC_RD_MODE32");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
    {
        perror("ioctl SPI_IOC_RD_LSB_FIRST");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
    {
        perror("ioctl SPI_IOC_RD_BITS_PER_WORD");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0)
    {
        perror("ioctl SPI_IOC_RD_MAX_SPEED_HZ");
        return -1;
    }

    printf("spi mode 0x%x, %d bits %sper word, %u Hz max\n", mode, bits, lsb ? "(lsb first) " : "", speed);

    return 0;
}

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 3)
    {
        fprintf(stderr, "invalid argument number\n");

        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDWR);

    if (fd < 0)
    {
        perror("opennig");

        return EXIT_FAILURE;
    }

    dump_status(fd);

    char buffer1[256];
    char buffer2[256];
    int size;

    if (str_2_hex(buffer1, argv[2], &size) < 0)
    {
        fprintf(stderr, "invalid argument %s\n", argv[2]);
    }
    else
    {
        if (hex_2_str(buffer2, buffer1, size) < 0)
        {

            fprintf(stderr, "invalid argument in hex to str\n");
        }
        else
        {

            fprintf(stdout, "reconverted %s\n", buffer2);
        }
    }

    if (close(fd) < 0)
    {
        perror("closing");
    }

    return EXIT_SUCCESS;
}
