#ifndef FIFO_H
#define FIFO_H

#include <array>
#include <cstddef>
#include <string>
#include <sstream>

template <typename T>
class Fifo
{
public:
    explicit Fifo(std::size_t capacity)
        : data_(new T[capacity]),
          capacity_(capacity)
    {
    }

    ~Fifo()
    {
        delete[] data_;
    }

    Fifo(const Fifo &) = delete;
    Fifo &operator=(const Fifo &) = delete;

    bool push(const T &value)
    {
        if (full())
            return false;

        data_[head_] = value;
        head_ = (head_ + 1) % capacity_;

        ++size_;

        return true;
    }

    std::size_t push(const T *values, std::size_t count)
    {
        std::size_t pushed = 0;

        while (pushed < count && !full())
        {
            data_[head_] = values[pushed];
            head_ = (head_ + 1) % capacity_;
            ++size_;
            ++pushed;
        }

        return pushed;
    }

    bool peek(T &value) const
    {
        if (empty())
            return false;

        value = data_[tail_];

        return true;
    }

    std::size_t peek(T *values, std::size_t count) const
    {
        if (count > size_)
            count = size_;

        std::size_t pos = tail_;

        for (std::size_t i = 0; i < count; ++i)
        {
            values[i] = data_[pos];
            pos = (pos + 1) % capacity_;
        }

        return count;
    }

    std::size_t consume(std::size_t count)
    {
        if (count > size_)
            count = size_;

        tail_ = (tail_ + count) % capacity_;
        size_ -= count;

        return count;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    bool full() const
    {
        return size_ == capacity_;
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t available() const
    {
        return capacity_ - size_;
    }

    constexpr std::size_t capacity() const
    {
        return capacity_;
    }

    void clear()
    {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }

    bool pop(T &value)
    {
        if (empty())
            return false;

        value = data_[tail_];
        tail_ = (tail_ + 1) % capacity_;

        --size_;

        return true;
    }

    std::size_t pop(T *values, std::size_t count)
    {
        std::size_t popped = 0;
        while (popped < count && !empty())
        {
            values[popped] = data_[tail_];
            tail_ = (tail_ + 1) % capacity_;
            --size_;
            ++popped;
        }
        return popped;
    }

private:
    T *data_;
    std::size_t capacity_;

    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};

#endif