#include "ProcessToModem.h"

void ProcessToModem::init(Context *context)
{
    context->getSource()->init();
    context->getSink()->init();
}

void ProcessToModem::start(Context *context)
{
    context->getSource()->start();
    context->getSink()->start();
}

void ProcessToModem::run(Context *context, long int time)
{
    char b[1024];
    int r, t;
    context->getSource()->rx(b, sizeof(b), &r);
    if (r > 0) {
        /* FIXME manage retries */
        context->getSink()->tx(b, r, &t);
    }
}

void ProcessToModem::stop(Context *context)
{
    context->getSource()->stop();
    context->getSink()->stop();
}

