#include <iostream>
#include "Bureaucrat.hpp"

int main()
{
	std::cout << "\n=== Default Constructor ===" << '\n';
	{
		Bureaucrat a;
		std::cout << a;
	}

	std::cout << "\n=== Parameterized Constructors (valid) ===" << '\n';
	{
		Bureaucrat a("Alice", 1);
		Bureaucrat b("Bob", 150);
		Bureaucrat c("Charlie", 75);
		std::cout << a << b << c;
	}

	std::cout << "\n=== GradeTooHighException ===" << '\n';
	{
		try
		{
			Bureaucrat a("TooHigh", 0);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}
	{
		try
		{
			Bureaucrat a("Negative", -42);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	std::cout << "\n=== GradeTooLowException ===" << '\n';
	{
		try
		{
			Bureaucrat a("TooLow", 151);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}
	{
		try
		{
			Bureaucrat a("WayLow", 300);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	std::cout << "\n=== incrementGrade ===" << '\n';
	{
		Bureaucrat a("Up", 2);
		std::cout << a;
		a.incrementGrade();
		std::cout << "After increment: " << a;
		try
		{
			a.incrementGrade();
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	std::cout << "\n=== decrementGrade ===" << '\n';
	{
		Bureaucrat a("Down", 149);
		std::cout << a;
		a.decrementGrade();
		std::cout << "After decrement: " << a;
		try
		{
			a.decrementGrade();
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	std::cout << "\n=== Copy Constructor ===" << '\n';
	{
		Bureaucrat a("Original", 42);
		Bureaucrat b(a);
		std::cout << "Original: " << a;
		std::cout << "Copy: " << b;
	}

	std::cout << "\n=== Copy Assignment ===" << '\n';
	{
		Bureaucrat a("Source", 99);
		Bureaucrat b("Dest", 1);
		b = a;
		std::cout << "After assignment:" << '\n';
		std::cout << "a: " << a;
		std::cout << "b: " << b;
	}

	std::cout << "\n=== operator<< Test ===" << '\n';
	{
		Bureaucrat a("Display", 123);
		std::cout << a;
	}

	std::cout << "\n=== All tests passed! ===" << '\n';
	return 0;
}
