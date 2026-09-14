
#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include "GpioAbstract.h"

/* This is the standard Linux kernel mapping for GPIO */
/* Usually the chip has 4 ports—A, B, C, and D—each with 32 pins. */
/* All are accessible via the same dev file: /dev/gpiochip0. */

#define GPIO_NUM_PORTS (4)
#define GPIO_NUM_LINES (32)

typedef struct port_s
{
    int offset[GPIO_NUM_LINES];
} port_t;

class GpioModule : public GpioAbstract
{
public:
    GpioModule();
    GpioAbstract::Error start(void);
    GpioAbstract::Error configure(int port, int line, GpioAbstract::Type type);
    GpioAbstract::Error set(int port, int line, int value);
    GpioAbstract::Error get(int port, int line, int *value);
    GpioAbstract::Error stop(void);
    GpioAbstract::Error setDeviceName(const char *name);

protected:
private:
    int fdChip;
    port_t port[GPIO_NUM_PORTS];
    char deviceName[GPIO_DEV_NAME_SIZE];
};

#endif
