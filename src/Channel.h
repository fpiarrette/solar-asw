
#ifndef CHANNEL_H
#define CHANNEL_H

class Channel
{
public:
    enum Error {
        E_OK = 0,
        E_TRY = -1,
        E_ARG = -2,
        E_STA = -3,
        E_INT = 4
    };

    virtual Error init(void) = 0;
    virtual Error start(void) = 0;
    virtual Error tx(char *data, int size, int *transmited) = 0;
    virtual Error rx(char *data, int size, int *received) = 0;
    virtual Error stop(void) = 0;

protected:
private:
};

#endif
