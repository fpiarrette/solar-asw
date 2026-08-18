#include "utils.h"

#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

void utils_sleep(unsigned int ms)
{
    struct timespec ts;
    ts.tv_sec = 0L;
    ts.tv_nsec = ms * 1000000L;
    nanosleep(&ts, NULL);
}

long int utils_curr_time_in_ms(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}