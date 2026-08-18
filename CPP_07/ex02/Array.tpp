//? Default constructor
template <typename T>
Array<T>::Array() : _data(NULL), _size(0)
{
}

//? Parameterized constructor
template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n)
{
}

//? Copy constructor
template <typename T>
Array<T>::Array(const Array &src) : _data(NULL), _size(0)
{
    *this = src;
}

//? Copy assignment operator
template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
    if (this != &other)
    {
        delete[] _data;
        _size = other._size;
        _data = new T[_size];
        for (unsigned int i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
    return *this;
}

//? Destructor
template <typename T>
Array<T>::~Array()
{
    delete[] _data;
}

//? Subscript operator (non-const)
template <typename T>
T &Array<T>::operator[](unsigned int i)
{
    if (i >= _size)
        throw std::exception();
    return _data[i];
}

//? Subscript operator (const)
template <typename T>
const T &Array<T>::operator[](unsigned int i) const
{
    if (i >= _size)
        throw std::exception();
    return _data[i];
}

//? size()
template <typename T>
unsigned int Array<T>::size() const
{
    return _size;
}
