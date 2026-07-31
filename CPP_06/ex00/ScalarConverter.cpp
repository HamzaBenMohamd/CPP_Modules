#include "ScalarConverter.hpp"

// Default Constructor
ScalarConverter::ScalarConverter()
{
    std::cout << "Default Constructor called of ScalarConverter" << std::endl;
}

// Copy Constructor
ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
    std::cout << "Copy Constructor called of ScalarConverter" << std::endl;
    *this = copy;
}

// Destructor
ScalarConverter::~ScalarConverter()
{
    std::cout << "Destructor called of ScalarConverter" << std::endl;
}

// Copy Assignment Operator
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &assign)
{
    std::cout << "Copy Assignment Operator called of ScalarConverter" << std::endl;
    if (this != &assign)
    {
        // _member = assign._member;
    }
    return (*this);
}
