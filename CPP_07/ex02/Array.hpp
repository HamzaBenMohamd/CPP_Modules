#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <cstddef>
# include <stdexcept>

template <typename T>
class Array
{
    private:
        T *_data;
        unsigned int _size;

    public:
        Array();
        Array(unsigned int n);
        Array(const Array &src);
        Array &operator=(const Array &rhs);
        ~Array();

        T &operator[](unsigned int i);
        const T &operator[](unsigned int i) const;

        unsigned int size() const;
};

# include "Array.tpp"

#endif
