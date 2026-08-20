
#ifndef CHANNEL_H
#define CHANNEL_H

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
