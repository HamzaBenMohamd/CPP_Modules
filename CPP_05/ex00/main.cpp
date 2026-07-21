#include <iostream>
#include "Bureaucrat.hpp"

int main()
{
	// try
	// {
	// 	throw Bureaucrat::GradeTooHighException();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cout << e.what() << '\n';
	// }

	Bureaucrat a;
	std::cout << '[' << a.getName() << ']' << '\n';
	std::cout << '[' << a.getGrade() << ']' << '\n';
	
	return 0;
}
//