#include "NotFoundException.hpp"

const char *NotFoundException::what() const throw()
{
    return "Value not found in container";
}

//! => If any non-interface class is not in orthodox canonical class form, do not grade this exercise.
