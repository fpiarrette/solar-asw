#include "ProcessFromModem.h"

#include <string.h>

void ProcessFromModem::start(void)
{
    write = 0;
}

void ProcessFromModem::run(void)
{
    char b[256];
    int r;
    channelSpi.receive(b, sizeof(b), &r);
    if (r > 0) {
        memcpy(&buffer[write], b, r);
        write += r;
        if (write > PROCESS_FROM_MODEM_LIMIT) {
            channelSocket.send(buffer, write);
            write = 0;
        }
    }
}
