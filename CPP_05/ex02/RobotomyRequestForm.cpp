#include "RobotomyRequestForm.hpp"

// Default Constructor
RobotomyRequestForm::RobotomyRequestForm()
{
    std::cout << "Default Constructor called of RobotomyRequestForm" << std::endl;
}

// Parameterized Constructor
RobotomyRequestForm::RobotomyRequestForm(std::string target)
{
    std::cout << "Parameterized Constructor called of RobotomyRequestForm" << std::endl;
}

// Copy Constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &copy)
{
    std::cout << "Copy Constructor called of RobotomyRequestForm" << std::endl;
    *this = copy;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "Destructor called of RobotomyRequestForm" << std::endl;
}

// Copy Assignment Operator
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &assign)
{
    std::cout << "Copy Assignment Operator called of RobotomyRequestForm" << std::endl;
    if (this != &assign)
    {
        // _member = assign._member;
    }
    return (*this);
}

//
void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{

}
