#include "Form.hpp"

// Default Constructor
Form::Form() : _name("someone"), _gradeSign(10), _gradeExec(20), _signed(false)
{
    std::cout << "Default Constructor called of Form" << std::endl;
}

// Parameterized Constructor
Form::Form(std::string name, int gradeSign, int gradeExec) : _name(name), _gradeSign(gradeSign), _gradeExec(gradeExec), _signed(false)
{
    std::cout << "Parameterized Constructor called of Form" << std::endl;
    if (gradeSign < 1 || gradeExec < 1)
		throw Form::GradeTooHighException();
	else if (gradeSign > 150 || gradeExec > 150)
		throw Form::GradeTooLowException();
}

// Copy Constructor
Form::Form(const Form &copy) : _name(copy._name), _gradeSign(copy._gradeSign), _gradeExec(copy._gradeExec), _signed(copy._signed)
{
    std::cout << "Copy Constructor called of Form" << std::endl;
}

// Destructor
Form::~Form()
{
    std::cout << "Destructor called of Form" << std::endl;
}

// Copy Assignment Operator
Form &Form::operator=(const Form &assign)
{
    std::cout << "Copy Assignment Operator called of Form" << std::endl;
    if (this != &assign)
    {
        this->_signed = assign._signed;
    }
    return (*this);
}

// Returns the error description for a Form grade that is too high
const char *Form::GradeTooHighException::what() const throw()
{
	return "Form grade too high!";
}

// Returns the error description for a Form grade that is too low
const char *Form::GradeTooLowException::what() const throw()
{
	return "Form grade too low!";
}

// Returns the Form's name
const std::string& Form::getName() const
{
    return this->_name;
}

// Returns the grade required to sign the Form
int Form::getGradeSign() const
{
    return this->_gradeSign;
}

// Returns the grade required to execute the Form
int Form::getGradeExec() const
{
    return this->_gradeExec;
}

// Returns whether the Form is signed
bool Form::getSigned() const
{
    return this->_signed;
}

// Signs the Form if the Bureaucrat's grade is high enough; throws GradeTooLowException otherwise
void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() <= this->_gradeSign)
        this->_signed = true;
    else
        throw Form::GradeTooLowException();
}

// Overloads the << operator to print the Form's complete state
std::ostream &operator<<(std::ostream &out, const Form &form)
{
    out << "Form " << form.getName()
        << ", signed: " << (form.getSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeSign()
        << ", grade to exec: " << form.getGradeExec()
        << '\n';
    return out;
}
