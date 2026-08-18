
#ifndef CHANNEL_H
#define CHANNEL_H

class Channel
{
public:
    virtual void init(void) = 0;
    virtual void start(void) = 0;
    virtual void send(char *data, int size) = 0;
    virtual void receive(char *data, int size, int *received) = 0;
    virtual void stop(void) = 0;
};

#endif
