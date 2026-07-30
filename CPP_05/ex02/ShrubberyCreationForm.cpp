#include "ShrubberyCreationForm.hpp"

//? Default Constructor
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("ShrubberyCreationForm")
{
    std::cout << "Default Constructor called of ShrubberyCreationForm" << std::endl;
}

//? Parameterized Constructor
ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
    std::cout << "Parameterized Constructor called of ShrubberyCreationForm" << std::endl;
}

//? Copy Constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy) : AForm(copy), _target(copy._target)
{
    std::cout << "Copy Constructor called of ShrubberyCreationForm" << std::endl;
}

//? Destructor
ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "Destructor called of ShrubberyCreationForm" << std::endl;
}

//? Copy Assignment Operator
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &assign)
{
    std::cout << "Copy Assignment Operator called of ShrubberyCreationForm" << std::endl;
    if (this != &assign)
    {
        AForm::operator=(assign);
        this->_target = assign._target;
    }
    return (*this);
}

//? Executes the shrubbery creation action
void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (!getSigned())
        throw AForm::NotSignedException();
    else if (executor.getGrade() > getGradeExec())
        throw AForm::GradeTooLowException();

    std::ofstream outfile((_target + "_shrubbery").c_str());
    if (outfile.is_open())
    {
        outfile << "       _-_\n"
        << "    /~~   ~~\\\n"
        << " /~~         ~~\\\n"
        << "{               }\n"
        << " \\  _-     -_  /\n"
        << "   ~  \\\\ //  ~\n"
        << "_- -   | | _- _\n"
        << "  _ -  | |   -_\n"
        << "      // \\\\\\\n";
        outfile.close();
    }
    else
        std::cout << "Error opening file." << '\n';
}
