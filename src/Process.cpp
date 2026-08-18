#include "Process.h"

void Process::init(void)
{
    channelSocket.init();
    channelSpi.init();
}

void Process::start(void)
{
    channelSocket.start();
    channelSpi.start();
}

void Process::stop(void)
{
    channelSocket.stop();
    channelSpi.stop();
}
