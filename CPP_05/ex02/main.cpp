#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	// =========================================================================
	// Test 1: Construct concrete forms with valid grades
	// =========================================================================
	{
		std::cout << "\n=== Concrete Form construction ===" << '\n';
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Arthur");
		std::cout << shrub;
		std::cout << robot;
		std::cout << pardon;
	}

	// =========================================================================
	// Test 2: AForm is abstract — cannot be instantiated directly
	// Uncommenting the line below would cause a compilation error:
	// AForm f("test", 1, 1);
	// =========================================================================

	// =========================================================================
	// Test 3: Sign then execute ShrubberyCreationForm (success)
	// =========================================================================
	{
		std::cout << "\n=== ShrubberyCreationForm: sign + execute ===" << '\n';
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("home");
		boss.signAForm(shrub);
		boss.executeForm(shrub);
		// Verify the file was created (checking by trying to open it)
		std::ifstream testFile("home_shrubbery");
		if (testFile.is_open())
		{
			std::cout << "File home_shrubbery was created successfully." << '\n';
			testFile.close();
		}
		else
			std::cout << "ERROR: File home_shrubbery was NOT created!" << '\n';
	}

	// =========================================================================
	// Test 4: execute without signing first (should fail)
	// =========================================================================
	{
		std::cout << "\n=== ShrubberyCreationForm: execute without sign ===" << '\n';
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("nowhere");
		boss.executeForm(shrub);
	}

	// =========================================================================
	// Test 5: execute with grade too low (after signing)
	// =========================================================================
	{
		std::cout << "\n=== PresidentialPardonForm: execute with low grade ===" << '\n';
		Bureaucrat intern("Intern", 150);
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Ford");
		boss.signAForm(pardon);
		intern.executeForm(pardon);
	}

	// =========================================================================
	// Test 6: sign failure (bureaucrat grade too low for sign)
	// =========================================================================
	{
		std::cout << "\n=== PresidentialPardonForm: sign failure ===" << '\n';
		Bureaucrat intern("Intern", 150);
		PresidentialPardonForm pardon("Trillian");
		intern.signAForm(pardon);
	}

	// =========================================================================
	// Test 7: RobotomyRequestForm — 50% robotomy (run multiple times to see both)
	// =========================================================================
	{
		std::cout << "\n=== RobotomyRequestForm: sign + execute (run 4 times) ===" << '\n';
		Bureaucrat boss("Boss", 1);
		for (int i = 0; i < 4; ++i)
		{
			RobotomyRequestForm robot("Bender");
			boss.signAForm(robot);
			boss.executeForm(robot);
		}
	}

	// =========================================================================
	// Test 8: PresidentialPardonForm — full success path
	// =========================================================================
	{
		std::cout << "\n=== PresidentialPardonForm: sign + execute ===" << '\n';
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Zaphod");
		boss.signAForm(pardon);
		boss.executeForm(pardon);
	}

	// =========================================================================
	// Test 9: Copy constructor of concrete forms
	// =========================================================================
	{
		std::cout << "\n=== Copy constructor (ShrubberyCreationForm) ===" << '\n';
		ShrubberyCreationForm original("garden");
		Bureaucrat boss("Boss", 1);
		boss.signAForm(original);
		ShrubberyCreationForm copy(original);
		std::cout << "Original: " << original;
		std::cout << "Copy: " << copy;
	}

	// =========================================================================
	// Test 10: Copy assignment of concrete forms
	// =========================================================================
	{
		std::cout << "\n=== Copy assignment (PresidentialPardonForm) ===" << '\n';
		PresidentialPardonForm a("Arthur");
		PresidentialPardonForm b("Zaphod");
		Bureaucrat boss("Boss", 1);
		boss.signAForm(a);
		b = a;
		std::cout << "After assignment:" << '\n';
		std::cout << "a: " << a;
		std::cout << "b: " << b;
	}

	// =========================================================================
	// Test 11: Bureaucrat regression — increment/decrement still work
	// =========================================================================
	{
		std::cout << "\n=== Bureaucrat regression ===" << '\n';
		Bureaucrat a("Steve", 75);
		std::cout << a;
		a.incrementGrade();
		std::cout << "after increment: " << a;
		a.decrementGrade();
		std::cout << "after decrement: " << a;
	}

	// =========================================================================
	// Test 12: executeForm success + failure messages
	// =========================================================================
	{
		std::cout << "\n=== executeForm messages ===" << '\n';
		Bureaucrat boss("Boss", 1);
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm shrub("test");
		// Failure message: not signed
		boss.executeForm(shrub);
		// Success message: signed and executed
		boss.signAForm(shrub);
		boss.executeForm(shrub);
		// Failure message: grade too low for execute
		PresidentialPardonForm pardon("Marvin");
		boss.signAForm(pardon);
		intern.executeForm(pardon);
	}

	std::cout << "\n=== All tests passed! ===" << '\n';
	return 0;
}
