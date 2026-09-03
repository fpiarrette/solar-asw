
#ifndef GPIO_ABSTRACT_H
#define GPIO_ABSTRACT_H

#define GPIO_NUM_LINES (32)
#define GPIO_DEV_NAME_SIZE (256)

class GpioAbstract
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

    virtual GpioAbstract::Error start(void) = 0;
    virtual GpioAbstract::Error configure(int line, Type type) = 0;
    virtual GpioAbstract::Error set(int line, int value) = 0;
    virtual GpioAbstract::Error get(int line, int *value) = 0;
    virtual GpioAbstract::Error stop(void) = 0;
    virtual GpioAbstract::Error setDeviceName(const char *name) = 0;

protected:
private:
};

#endif
