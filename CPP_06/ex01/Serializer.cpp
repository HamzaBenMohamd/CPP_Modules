#include "Serializer.hpp"

// Default Constructor
Serializer::Serializer()
{
    std::cout << "Default Constructor called of Serializer" << std::endl;
}

// Copy Constructor
Serializer::Serializer(const Serializer &copy)
{
    std::cout << "Copy Constructor called of Serializer" << std::endl;
    *this = copy;
}

// Destructor
Serializer::~Serializer()
{
    std::cout << "Destructor called of Serializer" << std::endl;
}

// Copy Assignment Operator
Serializer &Serializer::operator=(const Serializer &assign)
{
    std::cout << "Copy Assignment Operator called of Serializer" << std::endl;
    if (this != &assign)
    {
    }
    return (*this);
}

//? take a Data* pointer and view its bits as an unsigned integer.
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

//? take the raw integer and view its bits as a Data* again.
Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
