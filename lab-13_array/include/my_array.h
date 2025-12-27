#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <exception>

namespace lab_13
{
    // non-boolean specialization
    template <typename T, std::size_t N>
    class my_array
    {
    public:
        my_array();
        ~my_array();
        T &at(std::size_t index);
        T &operator[](std::size_t index);
        const T &at(std::size_t index) const;
        const T &operator[](std::size_t index) const;

        bool empty() const;
        std::size_t size() const;

        void fill(T val);

    private:
        T array_[N] = {};
    };

    template <typename T, std::size_t N>
    my_array<T, N>::my_array() {}

    template <typename T, std::size_t N>
    my_array<T, N>::~my_array() {}

    template <typename T, std::size_t N>
    void my_array<T, N>::fill(T val)
    {
        for (std::size_t i = 0; i < N; ++i)
            array_[i] = val;
    }

    template <typename T, std::size_t N>
    std::size_t my_array<T, N>::size() const
    {
        return N;
    }

    template <typename T, std::size_t N>
    bool my_array<T, N>::empty() const
    {
        return !(N > 0);
    }

    template <typename T, std::size_t N>
    T &my_array<T, N>::at(std::size_t index)
    {
        if (index >= N)
            throw std::out_of_range("index out of range");
        return array_[index];
    }

    template <typename T, std::size_t N>
    T &my_array<T, N>::operator[](std::size_t index)
    {
        return array_[index];
    }

    template <typename T, std::size_t N>
    const T &my_array<T, N>::at(std::size_t index) const
    {
        if (index >= N)
            throw std::out_of_range("index out of range");
        return array_[index];
    }

    template <typename T, std::size_t N>
    const T &my_array<T, N>::operator[](std::size_t index) const
    {
        return array_[index];
    }

    // end of non-boolean specialization
    // Bool Proxi logic
    class BoolProxi
    {
    public:
        BoolProxi(char &, std::size_t);
        BoolProxi(const char &, const std::size_t);
        BoolProxi &operator=(const BoolProxi &);
        BoolProxi &operator=(const bool);
        operator bool() const;

    private:
        std::size_t index_;
        char *val_;
    };
    
    BoolProxi::BoolProxi(char &ch, std::size_t index): index_(index), val_(&ch) {}
    BoolProxi::BoolProxi(const char &ch, std::size_t index): index_(index), val_(const_cast<char*>(&ch)) {}

    BoolProxi &BoolProxi::operator=(const BoolProxi &bp)
    {
        *val_ &= ~((1 << index_));
        if((*bp.val_) & (1 << bp.index_))
            *val_ |= (1 << index_);
        return *this;
    }

    BoolProxi &BoolProxi::operator=(const bool b)
    {
        *val_ &= ~((1 << index_));
        if(b)
            *val_ |= (1 << index_);
        return *this;
    }


    BoolProxi::operator bool() const{
        return *val_ & (1 << index_);
    }

    // end of Bool Proxi logic
    // start of my_array bool specializaion

    template <std::size_t N>
    class my_array<bool, N>
    {
    public:
        my_array();
        ~my_array();
        BoolProxi at(std::size_t index);
        BoolProxi operator[](std::size_t index);
        const BoolProxi at(std::size_t index) const;
        const BoolProxi operator[](std::size_t index) const;

        bool empty() const;
        std::size_t size() const;

        void fill(bool val);

    private:
        char array_[(N + 7) / 8] = {};
    };

    template <std::size_t N>
    std::size_t my_array<bool, N>::size() const
    {
        return N;
    }

    template <std::size_t N>
    bool my_array<bool, N>::empty() const
    {
        return !(N > 0);
    }

    template <std::size_t N>
    my_array<bool, N>::my_array() {}

    template <std::size_t N>
    my_array<bool, N>::~my_array() {}

    template <std::size_t N>
    BoolProxi my_array<bool, N>::at(std::size_t index)
    {
        if (index >= N)
            throw std::out_of_range("index out of range");
        return BoolProxi(array_[index / 8], index % 8);
    }

    template <std::size_t N>
    BoolProxi my_array<bool, N>::operator[](std::size_t index)
    {
        return BoolProxi(array_[index / 8], index % 8);
    }

    template <std::size_t N>
    const BoolProxi my_array<bool, N>::at(std::size_t index) const
    {
        if (index >= N)
            throw std::out_of_range("index out of range");
        return BoolProxi(array_[index / 8], index % 8);
    }

    template <std::size_t N>
    const BoolProxi my_array<bool, N>::operator[](std::size_t index) const
    {
        return BoolProxi(array_[index / 8], index % 8);
    }

    template <std::size_t N>
    void my_array<bool, N>::fill(bool val)
    {
        for (std::size_t i = 0; i < (N + 7) / 8; ++i)
        {
            for (std::size_t j = 0; j < 8; ++j)
            {
                if (i * 8 + j >= N)
                    continue;
                else
                {
                    array_[i] &= ~((1 << j));
                    if (val)
                        array_[i] |= (1 << j);
                }
            }
        }
    }

    // end of bool specialization
} // namespace lab_13

#endif // MY_ARRAY_H_
