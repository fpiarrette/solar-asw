#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <array>
#include <cstddef>

template <typename T, std::size_t N>
class CircularBuffer
{
public:
    bool push(const T &value)
    {
        if (full())
            return false;

        data_[head_] = value;
        head_ = (head_ + 1) % N;
        ++size_;

        return true;
    }

    std::size_t push(const T *values, std::size_t count)
    {
        std::size_t pushed = 0;

        while (pushed < count && !full())
        {
            data_[head_] = values[pushed];
            head_ = (head_ + 1) % N;
            ++size_;
            ++pushed;
        }

        return pushed;
    }

    std::size_t peek(T *values, std::size_t count) const
    {
        if (count > size_)
            count = size_;

        std::size_t pos = tail_;

        for (std::size_t i = 0; i < count; ++i)
        {
            values[i] = data_[pos];
            pos = (pos + 1) % N;
        }

        return count;
    }

    std::size_t consume(std::size_t count)
    {
        if (count > size_)
            count = size_;

        tail_ = (tail_ + count) % N;
        size_ -= count;

        return count;
    }

    void clear()
    {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    bool full() const
    {
        return size_ == N;
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t free() const
    {
        return N - size_;
    }

    constexpr std::size_t capacity() const
    {
        return N;
    }

private:
    std::array<T, N> data_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};

#endif