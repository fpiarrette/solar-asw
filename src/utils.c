#include "utils.h"

#include <time.h>
#include <stdlib.h>

void utils_sleep(unsigned int ms)
{
    struct timespec ts;
    ts.tv_sec = 0L;
    ts.tv_nsec = ms * 1000000L;
    nanosleep(&ts, NULL);
}
