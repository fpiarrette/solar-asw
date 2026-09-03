
#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include "GpioAbstract.h"

class GpioModule : public GpioAbstract
{
public:
    GpioModule();
    GpioAbstract::Error start(void);
    GpioAbstract::Error configure(int line, GpioAbstract::Type type);
    GpioAbstract::Error set(int line, int value);
    GpioAbstract::Error get(int line, int *value);
    GpioAbstract::Error stop(void);
    GpioAbstract::Error setDeviceName(const char *name);

protected:
private:
    int fdChip;
    int fdLine[GPIO_NUM_LINES];
    char deviceName[GPIO_DEV_NAME_SIZE];
};

#endif
