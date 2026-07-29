#include "AForm.hpp"

// Default Constructor
AForm::AForm() : _name("someone"), _gradeSign(10), _gradeExec(20), _signed(false)
{
    std::cout << "Default Constructor called of AForm" << std::endl;
}

// Parameterized Constructor
AForm::AForm(std::string name, int gradeSign, int gradeExec) : _name(name), _gradeSign(gradeSign), _gradeExec(gradeExec), _signed(false)
{
    std::cout << "Parameterized Constructor called of AForm" << std::endl;
    if (gradeSign < 1 || gradeExec < 1)
		throw AForm::GradeTooHighException();
	else if (gradeSign > 150 || gradeExec > 150)
		throw AForm::GradeTooLowException();
}

// Copy Constructor
AForm::AForm(const AForm &copy) : _name(copy._name), _gradeSign(copy._gradeSign), _gradeExec(copy._gradeExec), _signed(copy._signed)
{
    std::cout << "Copy Constructor called of AForm" << std::endl;
}

// Destructor
AForm::~AForm()
{
    std::cout << "Destructor called of AForm" << std::endl;
}

// Copy Assignment Operator
AForm &AForm::operator=(const AForm &assign)
{
    std::cout << "Copy Assignment Operator called of AForm" << std::endl;
    if (this != &assign)
    {
        this->_signed = assign._signed;
    }
    return (*this);
}

// Returns the error description for a AForm grade that is too high
const char *AForm::GradeTooHighException::what() const throw()
{
	return "AForm grade too high!";
}

// Returns the error description for a AForm grade that is too low
const char *AForm::GradeTooLowException::what() const throw()
{
	return "AForm grade too low!";
}

const char *AForm::NotSignedException::what() const throw()
{
	return "Form Is Not Signed!";
}

// Returns the AForm's name
const std::string& AForm::getName() const
{
    return this->_name;
}

// Returns the grade required to sign the AForm
int AForm::getGradeSign() const
{
    return this->_gradeSign;
}

// Returns the grade required to execute the AForm
int AForm::getGradeExec() const
{
    return this->_gradeExec;
}

// Returns whether the AForm is signed
bool AForm::getSigned() const
{
    return this->_signed;
}

// Signs the AForm if the Bureaucrat's grade is high enough; throws GradeTooLowException otherwise
void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() <= this->_gradeSign)
        this->_signed = true;
    else
        throw AForm::GradeTooLowException();
}

// Overloads the << operator to print the AForm's complete state
std::ostream &operator<<(std::ostream &out, const AForm &form)
{
    out << "AForm " << form.getName()
        << ", signed: " << (form.getSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeSign()
        << ", grade to exec: " << form.getGradeExec()
        << '\n';
    return out;
}
