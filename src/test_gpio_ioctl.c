#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/gpio.h>

int do_read(int fd, char *_line)
{
    struct gpiohandle_request request;
    struct gpiohandle_data data;

    int line;

    if (sscanf(_line, "%d", &line) != 1)
    {
        fprintf(stderr, "invalid argument: %s\n", _line);

        return -1;
    }

    memset(&request, 0, sizeof(request));

    request.lineoffsets[0] = line;
    request.lines = 1;
    request.flags = GPIOHANDLE_REQUEST_INPUT;

    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &request) < 0)
    {
        perror("getting the line");

        return -1;
    }

    printf("line file descriptor %d\n", request.fd);

    if (ioctl(request.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) < 0)
    {
        perror("reading the line");

        close(request.fd);

        return -1;
    }

    printf("line %d value %d read\n", line, data.values[0]);

    if (close(request.fd) < 0)
    {
        perror("closing line file descriptor");

        return -1;
    }

    return 0;
}

int do_write(int fd, char *_line, char *_value)
{
    struct gpiohandle_request request;
    struct gpiohandle_data data;

    int line, value;

    if (sscanf(_line, "%d", &line) != 1)
    {
        fprintf(stderr, "invalid argument: %s\n", _line);

        return -1;
    }

    if (sscanf(_value, "%d", &value) != 1)
    {
        fprintf(stderr, "invalid argument: %s\n", _value);

        return -1;
    }

    request.lines = 1;
    request.lineoffsets[0] = line;
    request.flags = GPIOHANDLE_REQUEST_OUTPUT;

    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &request))
    {
        perror("getting the line");

        return -1;
    }

    printf("line file descriptor %d\n", request.fd);

    data.values[0] = (value != 0) ? 1 : 0;

    if (ioctl(request.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0)
    {
        perror("writing the line");

        if (close(request.fd) < 0)
        {
            perror("closing line file descriptor");
        }

        return -1;
    }

    if (close(request.fd) < 0)
    {
        perror("closing line file descriptor");
    }

    printf("line %d set to %d value\n", line, data.values[0]);

    return 0;
}

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "invalid numeber of arguments\n");
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDWR);

    if (fd < 0)
    {
        perror("opening device");
        return EXIT_FAILURE;
    }

    if (argc == 3)
    {
        do_read(fd, argv[2]);
    }
    else if (argc == 4)
    {
        do_write(fd, argv[2], argv[3]);
    }

    if (close(fd) < 0)
    {
        perror("closing device");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
