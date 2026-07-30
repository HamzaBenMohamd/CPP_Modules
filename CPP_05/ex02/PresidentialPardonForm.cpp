#include "PresidentialPardonForm.hpp"

//? Default Constructor
PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), _target("PresidentialPardonForm")
{
    std::cout << "Default Constructor called of PresidentialPardonForm" << std::endl;
}

//? Parameterized Constructor
PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5), _target(target)
{
    std::cout << "Parameterized Constructor called of PresidentialPardonForm" << std::endl;
}

//? Copy Constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy) : AForm(copy), _target(copy._target)
{
    std::cout << "Copy Constructor called of PresidentialPardonForm" << std::endl;
}

//? Destructor
PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "Destructor called of PresidentialPardonForm" << std::endl;
}

//? Copy Assignment Operator
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &assign)
{
    std::cout << "Copy Assignment Operator called of PresidentialPardonForm" << std::endl;
    if (this != &assign)
    {
        AForm::operator=(assign);
        this->_target = assign._target;
    }
    return (*this);
}

//? Executes the presidential pardon action
void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (!getSigned())
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeExec())
        throw AForm::GradeTooLowException();

    std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << '\n';
}
