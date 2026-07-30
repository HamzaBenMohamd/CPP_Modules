#include "Intern.hpp"

//? Default Constructor
Intern::Intern()
{
    std::cout << "Default Constructor called of Intern" << std::endl;
}

//? Copy Constructor
Intern::Intern(const Intern &copy)
{
    std::cout << "Copy Constructor called of Intern" << std::endl;
    *this = copy;
}

//? Destructor
Intern::~Intern()
{
    std::cout << "Destructor called of Intern" << std::endl;
}

//? Copy Assignment Operator
Intern &Intern::operator=(const Intern &assign)
{
    std::cout << "Copy Assignment Operator called of Intern" << std::endl;
    if (this != &assign)
    {
    }
    return (*this);
}

//?
AForm *Intern::makeShrubbery(std::string target)
{
    return new ShrubberyCreationForm(target);
}

//?
AForm *Intern::makeRobotomy(std::string target)
{
    return new RobotomyRequestForm(target);
}

//?
AForm *Intern::makePardon(std::string target)
{
    return new PresidentialPardonForm(target);
}

//? 
AForm *Intern::makeForm(std::string formName, std::string target)
{
    std::string formNames[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    AForm *(Intern::*formMakers[3])(std::string target) = {
        &Intern::makeShrubbery,
        &Intern::makeRobotomy,
        &Intern::makePardon
    };

    for (int i = 0; i < 3; i++)
    {
        if (formName == formNames[i])
        {
            std::cout << "Intern creates " << formName << '\n';
            return (this->*formMakers[i])(target);
        }
    }
    std::cout << "Invalid form name" << '\n';
    return NULL;
}
