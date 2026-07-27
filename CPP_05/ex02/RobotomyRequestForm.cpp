#include "RobotomyRequestForm.hpp"

// Default Constructor
RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("RobotomyRequestForm")
{
    std::cout << "Default Constructor called of RobotomyRequestForm" << std::endl;
}

// Parameterized Constructor
RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target)
{
    std::cout << "Parameterized Constructor called of RobotomyRequestForm" << std::endl;
}

// Copy Constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &copy) : AForm(copy), _target(copy._target)
{
    std::cout << "Copy Constructor called of RobotomyRequestForm" << std::endl;
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
        AForm::operator=(assign);
        this->_target = assign._target;
    }
    return (*this);
}

// Executes the robotomy request action
void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
    if (!getSigned())
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeExec())
        throw AForm::GradeTooLowException();

    std::cout << "* DRILLING NOISES * Bzzzzzzzrrrrrrrr! *" << '\n';

    std::srand(std::time(0));

    if (std::rand() % 2 == 0)
        std::cout << _target << " has been robotomized successfully!" << '\n';
    else
        std::cout << "Robotomy failed! " << _target << " is still alive." << '\n';
}
