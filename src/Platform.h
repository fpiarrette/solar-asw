
#ifndef PLATFORM_H
#define PLATFORM_H

class Platform
{
public:
    static Platform *getInstance(void);
    void init(void);
    void shutdown(void);

protected:
    Platform();
private:
    static Platform instance;
};

#endif
