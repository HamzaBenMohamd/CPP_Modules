// Array.tpp : template implementations, included at the end of Array.hpp.
// Every definition must repeat "template <typename T>" and be fully qualified
// with Array<T>:: so the compiler knows which template we are defining.

// Default constructor: builds an EMPTY array.
// - no allocation is performed (subject: no preventive allocation)
// - _data is NULL and _size is 0 => a valid but empty array.
template <typename T>
Array<T>::Array() : _data(NULL), _size(0)
{
}

// Constructor with size n: allocates n default-initialized elements.
// NOTE: new T[n]() uses parentheses, which VALUE-initializes every element:
// ints become 0, std::string becomes "", etc.
// (subject tip: int *a = new int(); then *a is 0)
template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n)
{
}

// Copy constructor: must make a DEEP copy so that modifying the copy never
// affects the original (and vice-versa). We delegate to operator= below.
template <typename T>
Array<T>::Array(const Array &src) : _data(NULL), _size(0)
{
    *this = src;
}

// Destructor: free the memory allocated with new[].
// delete[] matches new[] (subject REQUIRES operator new[] for allocation).
// Safe on NULL (empty array), since delete[] on NULL is a no-op.
template <typename T>
Array<T>::~Array()
{
    delete[] _data;
}

// Copy assignment operator.
// Steps:
//   1. Self-assignment check (a = a would otherwise delete our own data).
//   2. Release the previous buffer.
//   3. Allocate a fresh buffer of the same size, value-initialized.
//   4. Copy element by element.
// A fresh allocation guarantees no shared memory with rhs => deep copy.
template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
    if (this != &rhs)
    {
        delete[] _data;
        _size = rhs._size;
        _data = new T[_size]();
        for (unsigned int i = 0; i < _size; i++)
            _data[i] = rhs._data[i];
    }
    return *this;
}

// Subscript operator (non-const): read/write access to element i.
// If i is out of bounds we must throw an std::exception (subject).
template <typename T>
T &Array<T>::operator[](unsigned int i)
{
    if (i >= _size)
        throw std::exception();
    return _data[i];
}

// Subscript operator (const): read-only access for const Array objects.
// Same bounds check; returns a const reference so the caller cannot modify it.
template <typename T>
const T &Array<T>::operator[](unsigned int i) const
{
    if (i >= _size)
        throw std::exception();
    return _data[i];
}

// size(): returns how many elements the array holds.
// Declared const because it must NOT modify the instance (subject).
template <typename T>
unsigned int Array<T>::size() const
{
    return _size;
}
