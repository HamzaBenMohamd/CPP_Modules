#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	{
		std::cout << "\n=== Construction ===" << '\n';
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Arthur");
		std::cout << shrub << robot << pardon;
	}

	{
		std::cout << "\n=== ShrubberyCreationForm: sign + execute ===" << '\n';
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("home");
		boss.signAForm(shrub);
		boss.executeForm(shrub);
	}

	{
		std::cout << "\n=== RobotomyRequestForm: sign + execute ===" << '\n';
		Bureaucrat boss("Boss", 1);
		for (int i = 0; i < 2; ++i)
		{
			RobotomyRequestForm robot("Bender");
			boss.signAForm(robot);
			boss.executeForm(robot);
		}
	}

	{
		std::cout << "\n=== PresidentialPardonForm: sign + execute ===" << '\n';
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Arthur");
		boss.signAForm(pardon);
		boss.executeForm(pardon);
	}

	{
		std::cout << "\n=== Execute without signing ===" << '\n';
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("nowhere");
		boss.executeForm(shrub);
	}

	{
		std::cout << "\n=== Execute with low grade ===" << '\n';
		Bureaucrat boss("Boss", 1);
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon("Ford");
		boss.signAForm(pardon);
		intern.executeForm(pardon);
	}

	{
		std::cout << "\n=== Sign with low grade ===" << '\n';
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon("Trillian");
		intern.signAForm(pardon);
	}

	{
		std::cout << "\n=== executeForm messages ===" << '\n';
		Bureaucrat boss("Boss", 1);
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm shrub("test");
		boss.signAForm(shrub);
		boss.executeForm(shrub);
		PresidentialPardonForm pardon("Marvin");
		boss.signAForm(pardon);
		intern.executeForm(pardon);
	}

	return 0;
}
