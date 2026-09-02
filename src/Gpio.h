
#ifndef GPIO_H
#define GPIO_H

#define GPIO_NUM_LINES (32)
#define GPIO_DEV_NAME_SIZE (256)

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

    static Gpio *getInstance(void);

    Gpio::Error init(void);
    Gpio::Error start(void);
    Gpio::Error configure(int line, Type type);
    Gpio::Error set(int line, int value);
    Gpio::Error get(int line, int *value);
    Gpio::Error stop(void);
    Gpio::Error setDeviceName(const char *name);

protected:
private:
    static Gpio instance;
    int fdChip;
    int fdLine[GPIO_NUM_LINES];
    char deviceName[GPIO_DEV_NAME_SIZE];
};

#endif
