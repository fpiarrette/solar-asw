
#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#define CIRCULAR_BUFFER_SIZE (8 * 1024)

class CircularBuffer
{
public:
    CircularBuffer();
    void write(char *buffer, int size);
    void read(char *buffer, int size, int *read);
    int getAvailable(void);
    void rewind(int amount);

protected:
private:
    char buffer[CIRCULAR_BUFFER_SIZE];
    unsigned long int readIndex;
    unsigned long int writeIndex;
};

#endif
