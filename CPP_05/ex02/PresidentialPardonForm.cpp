#include "PresidentialPardonForm.hpp"

// Default Constructor
PresidentialPardonForm::PresidentialPardonForm()
{
    std::cout << "Default Constructor called of PresidentialPardonForm" << std::endl;
}

// Parameterized Constructor
PresidentialPardonForm::PresidentialPardonForm(std::string target)
{
    std::cout << "Parameterized Constructor called of PresidentialPardonForm" << std::endl;
}

// Copy Constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy)
{
    std::cout << "Copy Constructor called of PresidentialPardonForm" << std::endl;
    *this = copy;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "Destructor called of PresidentialPardonForm" << std::endl;
}

// Copy Assignment Operator
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &assign)
{
    std::cout << "Copy Assignment Operator called of PresidentialPardonForm" << std::endl;
    if (this != &assign)
    {
        // _member = assign._member;
    }
    return (*this);
}

//
void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{

}
