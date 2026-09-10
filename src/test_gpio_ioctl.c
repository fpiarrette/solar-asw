#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/gpio.h>

int try_close(int fd)
{
    if (close(fd) < 0)
    {
        perror("closing device");
        return -1;
    }
    return 0;
}

int do_read(int fd, char *l)
{
    struct gpio_v2_line_request request;
    struct gpio_v2_line_values values;
    int line, fd_line, v;

    if (sscanf(l, "%d", &line) != 1)
    {
        fprintf(stderr, "invalid argument: %s\n", l);

        return -1;
    }

    memset(&request, 0, sizeof(request));
/*
    request.num_lines = 1;
    request.offsets[0] = line;
    */
    /*request.config.flags = GPIO_V2_LINE_FLAG_INPUT;*/

    printf("line value %d\n", line);

    int r;
    if ((r = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &request)) < 0)
    {
        perror("configuring line");

        return -1;
    }

    fd_line = request.fd;

    printf("ioctl %d fd %d\n", r, fd_line);

    if (fd_line < 0)
    {

        fprintf(stderr, "line file descriptor is invalid\n");

        return -1;
    }

    /*****************************************/

#if 0

    memset(&values, 0, sizeof(values));

    values.mask = 1;

    if (ioctl(fd_line, GPIO_V2_LINE_GET_VALUES_IOCTL, &values) < 0)
    {
        perror("configuring line");

        return -1;
    }

    v = (values.bits & 1);

    printf("line value is %d", v);
#endif

    /*****************************************/

#if 0
    if (close(fd_line) < 0)
    {
        perror("closing line");
        return -1;
    }
#endif

    return 0;
}

int do_write(int fd, char *line, char *value)
{
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
