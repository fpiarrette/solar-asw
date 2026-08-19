#include "Process.h"

#ifndef PROCESS_FROM_MODEM_H
#define PROCESS_FROM_MODEM_H

class ProcessFromModem : public Process
{
public:
    void start(void);
    void run(long int time);
    void setTimeDeliveryLimit(int value);
    void setBufferSizeLimit(int value);
private:
    char buffer[8 * 1024];
    int write;
    long int timeBarrier;
    int timeDeliveryLimit;
    int bufferSizeLimit;
};

#endif
