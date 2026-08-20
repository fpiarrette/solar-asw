#include "Process.h"

#ifndef PROCESS_FROM_MODEM_H
#define PROCESS_FROM_MODEM_H

class ProcessFromModem : public Process
{
public:
    void init(Context *context);
    void start(Context *context);
    void run(Context *context, long int time);
    void stop(Context *context);
    void setTimeDeliveryLimit(int value);
    void setBufferSizeLimit(int value);

protected:
private:
    char buffer[8 * 1024];
    int write;
    long int timeBarrier;
    int timeDeliveryLimit;
    int bufferSizeLimit;
};

#endif
