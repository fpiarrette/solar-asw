#include "ProcessToModem.h"

void ProcessToModem::init(void)
{
    channelSocketServer.init();
    channelSpi.init();
}

void ProcessToModem::start(void)
{
    channelSocketServer.start();
    channelSpi.start();
}

void ProcessToModem::run(long int time)
{
    char b[1024];
    int r, t;
    channelSocketServer.rx(b, sizeof(b), &r);
    if (r > 0) {
        /* FIXME manage retries */
        channelSpi.tx(b, r, &t);
    }
}

void ProcessToModem::stop(void)
{
    channelSocketServer.stop();
    channelSpi.stop();
}

