
#ifndef CHANNEL_H
#define CHANNEL_H

#define CHANNEL_E_OK (0)
#define CHANNEL_E_ARG (-1)
#define CHANNEL_E_STA (-2)
#define CHANNEL_E_INT (-3)

class Channel
{
public:
    virtual void init(void) = 0;
    virtual void start(void) = 0;
    virtual void tx(char *data, int size) = 0;
    virtual void rx(char *data, int size, int *received) = 0;
    virtual void stop(void) = 0;

protected:
private:
};

#endif
