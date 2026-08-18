#include "ProcessToModem.h"

void ProcessToModem::run(long int time)
{
    char b[1024];
    int r;
    channelSocket.receive(b, sizeof(b), &r);
    if (r > 0) {
        channelSpi.send(b, r);
    }
}

