#include "Fifo.h"

#include <stdlib.h>
#include <iostream>

#define PRINT(_b)                                                                                         \
    do                                                                                                    \
    {                                                                                                     \
        char t[_b.size()];                                                                                \
        _b.peek(t, _b.size());                                                                            \
        std::cout << "c: " << _b.capacity() << ", s: " << _b.size() << ", a: " << _b.available() << " ["; \
        for (size_t n = 0; n < _b.size(); n++)                                                            \
        {                                                                                                 \
            std::cout << (int)t[n];                                                                       \
            if (n < (_b.size() - 1))                                                                      \
                std::cout << ", ";                                                                        \
        }                                                                                                 \
        std::cout << "]" << std::endl;                                                                    \
    } while (0)

int main(int argc, char *argv[])
{
    Fifo<char, 8> b;
    char d;

    std::cout << "empty: " << b.empty() << std::endl;
    std::cout << "full: " << b.full() << std::endl;
    std::cout << "size: " << b.size() << std::endl;
    std::cout << "available: " << b.available() << std::endl;

    PRINT(b);

    b.push(10);
    b.push(20);
    b.push(30);

    PRINT(b);

    b.pop(d);

    PRINT(b);

    b.push(d);

    PRINT(b);

    b.push(40);
    b.push(50);
    b.push(60);
    b.push(70);
    b.push(80);

    std::cout << "empty: " << b.empty() << std::endl;
    std::cout << "full: " << b.full() << std::endl;
    std::cout << "size: " << b.size() << std::endl;
    std::cout << "available: " << b.available() << std::endl;

    PRINT(b);

    b.clear();

    PRINT(b);

    std::cout << "empty: " << b.empty() << std::endl;
    std::cout << "full: " << b.full() << std::endl;
    std::cout << "size: " << b.size() << std::endl;
    std::cout << "available: " << b.available() << std::endl;

    b.push(1);
    b.push(2);
    b.push(3);

    PRINT(b);

    std::cout << "empty: " << b.empty() << std::endl;
    std::cout << "full: " << b.full() << std::endl;
    std::cout << "size: " << b.size() << std::endl;
    std::cout << "available: " << b.available() << std::endl;

    return EXIT_SUCCESS;
}
