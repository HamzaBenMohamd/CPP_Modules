#include "Bureaucrat.hpp"

//? Default Constructor
Bureaucrat::Bureaucrat() : _name("Anonymous"), _grade(5)
{
	std::cout << "Default Constructor called of Bureaucrat" << std::endl;
}

//? Parameters Constructor
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	std::cout << "Default Parameters Constructor called of Bureaucrat" << std::endl;

	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = grade;
}

//? Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat &copy) : _name(copy._name), _grade(copy._grade)
{
	std::cout << "Copy Constructor called of Bureaucrat" << std::endl;
}

//? Destructor
Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called of Bureaucrat" << std::endl;
}

//? Copy Assignment Operator
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &assign)
{
	std::cout << "Copy Assignment Operator called of Bureaucrat" << std::endl;
	if (this != &assign)
	{
		this->_grade = assign._grade;
	}
	return (*this);
}

//! --- custm exceptions ---

//? overrided what() fun of GradTooLowException class
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Too High grade!";
}

//? overrided what() fun of GradTooLowException class
const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Too Low grade!";
}

//! --- getters ---

//?
std::string Bureaucrat::getName() const
{
	return this->_name;
}

//?
int Bureaucrat::getGrade() const
{
	return this->_grade;
}

//! --- Action Methods ---

//?
void Bureaucrat::incrementGrade()
{
	// 5 => 4
	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

//?
void Bureaucrat::decrementGrade()
{
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

//?
std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << '.' << '\n';
	return out;
}
