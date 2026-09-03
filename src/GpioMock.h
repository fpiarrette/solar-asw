
#ifndef GPIO_MOCK_H
#define GPIO_MOCK_H

#include "GpioAbstract.h"

class GpioMock : public GpioAbstract
{
public:
    GpioAbstract::Error start(void);
    GpioAbstract::Error configure(int line, GpioAbstract::Type type);
    GpioAbstract::Error set(int line, int value);
    GpioAbstract::Error get(int line, int *value);
    GpioAbstract::Error stop(void);
    GpioAbstract::Error setDeviceName(const char *name);

protected:
private:
    static GpioMock instance;
};

#endif
