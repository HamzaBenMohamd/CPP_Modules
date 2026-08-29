#include "NotFoundException.hpp"

const char *NotFoundException::what() const throw()
{
    return "Value not found in container";
}
