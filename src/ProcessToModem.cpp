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
    int r;
    channelSocketServer.receive(b, sizeof(b), &r);
    if (r > 0) {
        channelSpi.send(b, r);
    }
}

void ProcessToModem::stop(void)
{
    channelSocketServer.stop();
    channelSpi.stop();
}

