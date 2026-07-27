#include "Bureaucrat.hpp"

// Default Constructor
Bureaucrat::Bureaucrat() : _name("Anonymous"), _grade(5)
{
	std::cout << "Default Constructor called of Bureaucrat" << std::endl;
}

// Parameterized Constructor with name and grade; throws on invalid grade
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	std::cout << "Parameterized Constructor called of Bureaucrat" << std::endl;

	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = grade;
}

// Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat &copy) : _name(copy._name), _grade(copy._grade)
{
	std::cout << "Copy Constructor called of Bureaucrat" << std::endl;
}

// Destructor
Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called of Bureaucrat" << std::endl;
}

// Copy Assignment Operator (copies grade only; name stays const)
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &assign)
{
	std::cout << "Copy Assignment Operator called of Bureaucrat" << std::endl;
	if (this != &assign)
	{
		this->_grade = assign._grade;
	}
	return (*this);
}

// Returns the error description for a grade that is too high
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Too High grade!";
}

// Returns the error description for a grade that is too low
const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Too Low grade!";
}

// Returns the Bureaucrat's name
const std::string& Bureaucrat::getName() const
{
	return this->_name;
}

// Returns the Bureaucrat's grade
int Bureaucrat::getGrade() const
{
	return this->_grade;
}

// Increments grade (raises rank by one); throws GradeTooHighException if grade is 1
void Bureaucrat::incrementGrade()
{
	if (this->_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

// Decrements grade (lowers rank by one); throws GradeTooLowException if grade is 150
void Bureaucrat::decrementGrade()
{
	if (this->_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

// Attempts to sign a AForm; prints success or failure message
void Bureaucrat::signAForm(AForm &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << getName() << " signed " << form.getName() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cout << getName() << " couldn't sign " << form.getName() << " because " << e.what() << '\n';
    }
}

// Attempts to execute a form
void Bureaucrat::executeForm(AForm const & form) const
{
    try
    {
        form.execute(*this);
        std::cout << getName() << " executed " << form.getName() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cout << getName() << " couldn't execute " << form.getName() << " because " << e.what() << '\n';
    }
}

// Overloads the << operator to print the Bureaucrat's info
std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << '.' << '\n';
	return out;
}
