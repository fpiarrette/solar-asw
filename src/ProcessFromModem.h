#include "Process.h"

#ifndef PROCESS_FROM_MODEM_H
#define PROCESS_FROM_MODEM_H

/* minimum number of bytes to deliver a packet (in bytes) */
#define PROCESS_FROM_MODEM_LIMIT (512)
/* time limit to deliver a packet even when size is not enough (ms) */
#define PROCESS_FROM_MODEM_NEXT_BARRIER (500)

class ProcessFromModem : public Process
{
public:
    void start(void);
    void run(long int time);

private:
    char buffer[8 * 1024];
    int write;
    long int timeBarrier;
};

#endif
