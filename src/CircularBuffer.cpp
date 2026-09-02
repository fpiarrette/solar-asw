#include "CircularBuffer.h"

#include <string.h>

CircularBuffer::CircularBuffer()
{
    memset(buffer, 0, CIRCULAR_BUFFER_SIZE);
    readIndex = 0;
    writeIndex = 0;
}

void CircularBuffer::write(char *b, int size)
{
    for (int n = 0; n < size; n++)
    {
        buffer[writeIndex % CIRCULAR_BUFFER_SIZE] = b[n];
        writeIndex++;
    }
}

void CircularBuffer::read(char *b, int size, int *read)
{
    if (size > getAvailable())
    {
        size = getAvailable();
    }

    for (int n = 0; n < size; n++)
    {
        b[n] = buffer[readIndex % CIRCULAR_BUFFER_SIZE];
        readIndex++;
    }

    *read = size;
}

int CircularBuffer::getAvailable(void)
{
    return writeIndex - readIndex;
}

void CircularBuffer::rewind(int amount)
{
    int unused;

    unused = CIRCULAR_BUFFER_SIZE - getAvailable();

    if (amount > unused)
    {
        amount = unused;
    }

    readIndex -= amount;
}
