#ifndef ARRAY_HPP
#define ARRAY_HPP

// Include guards: make the header safe against double inclusion
// (subject requires them, grade 0 otherwise).

#include <cstddef>    // NULL
#include <stdexcept>  // std::exception

// Class template: Array is a minimal wrapper around a dynamic C-style array.
// The template parameter T is the type of the stored elements, so the same
// class works for int, std::string, etc.
template <typename T>
class Array
{
private:
    T *_data;        // pointer to the heap-allocated elements
    unsigned int _size; // number of elements currently stored

public:
    // --- Orthodox Canonical Form (required from Module 02 to 09) ---
    Array();                                // default ctor: empty array
    Array(unsigned int n);                  // ctor: array of n elements
    Array(const Array &src);                // copy ctor: deep copy
    ~Array();                               // dtor: release memory
    Array &operator=(const Array &rhs);     // copy assignment: deep copy

    // --- Subscript access (subject) ---
    // Non-const version: allows both reading AND writing, e.g. arr[0] = 5.
    T &operator[](unsigned int i);
    // Const version: reading only. Needed so iterating a const Array compiles.
    const T &operator[](unsigned int i) const;

    // Returns the number of elements. const method: does not modify the object.
    unsigned int size() const;
};

// Member functions of a class template are "function templates" themselves,
// so (per the subject) they may live outside the .cpp files.
// They are included via the .tpp file below, keeping this header readable.
#include "Array.tpp"

#endif
