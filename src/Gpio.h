
#ifndef GPIO_H
#define GPIO_H

#define GPIO_DEV_NAME_SIZE (256)

#define GPIO_NUM_PORTS (4)
#define GPIO_NUM_LINES (32)

typedef struct port_s
{
    int line[GPIO_NUM_LINES];
} port_t;

class Gpio
{
public:
    enum Error
    {
        E_OK = 0,
        E_TRY = -1,
        E_ARG = -2,
        E_STA = -3,
        E_INT = 4
    };

    enum Type
    {
        NONE = 0,
        IN = 1,
        OUT = 2,
    };

    Gpio();
    Gpio::Error start(void);
    Gpio::Error configure(int port, int line, Type type);
    Gpio::Error set(int port, int line, int value);
    Gpio::Error get(int port, int line, int *value);
    Gpio::Error stop(void);
    Gpio::Error setDeviceName(const char *name);

protected:
private:
    int fdChip;
    port_t port[GPIO_NUM_PORTS];
    char deviceName[GPIO_DEV_NAME_SIZE];
};

#endif
