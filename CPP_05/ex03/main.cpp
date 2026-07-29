#include "Intern.hpp"


int main()
{
	Intern intern;

	{
		std::cout << "\n=== ShrubberyCreationForm via Intern ===" << '\n';
		AForm *f = intern.makeForm("shrubbery creation", "garden");
		if (f)
		{
			Bureaucrat boss("Boss", 1);
			boss.signAForm(*f);
			boss.executeForm(*f);
			delete f;
		}
	}

	{
		std::cout << "\n=== RobotomyRequestForm via Intern ===" << '\n';
		AForm *f = intern.makeForm("robotomy request", "Bender");
		if (f)
		{
			Bureaucrat boss("Boss", 1);
			boss.signAForm(*f);
			boss.executeForm(*f);
			delete f;
		}
	}

	{
		std::cout << "\n=== PresidentialPardonForm via Intern ===" << '\n';
		AForm *f = intern.makeForm("presidential pardon", "Arthur");
		if (f)
		{
			Bureaucrat boss("Boss", 1);
			boss.signAForm(*f);
			boss.executeForm(*f);
			delete f;
		}
	}

	{
		std::cout << "\n=== Invalid form name ===" << '\n';
		AForm *f = intern.makeForm("unknown form", "nowhere");
		if (!f)
			std::cout << "NULL pointer returned" << '\n';
	}

	return 0;
}
