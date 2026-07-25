#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	{
		std::cout << "\n=== Form construction ===" << '\n';
		Form a("TaxForm", 50, 25);
		std::cout << a;
	}

	{
		std::cout << "\n=== Form GradeTooHighException ===" << '\n';
		try
		{
			Form a("BadForm", 0, 50);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
		try
		{
			Form a("BadForm2", 50, -1);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	{
		std::cout << "\n=== Form GradeTooLowException ===" << '\n';
		try
		{
			Form a("BadForm", 151, 50);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
		try
		{
			Form a("BadForm2", 50, 200);
		}
		catch (const std::exception &e)
		{
			std::cout << "Caught: " << e.what() << '\n';
		}
	}

	{
		std::cout << "\n=== beSigned success ===" << '\n';
		Bureaucrat bob("Bob", 20);
		Form f("SecretForm", 50, 25);
		std::cout << f;
		bob.signForm(f);
		std::cout << f;
	}

	{
		std::cout << "\n=== beSigned failure ===" << '\n';
		Bureaucrat bob("Bob", 100);
		Form f("SecretForm", 50, 25);
		std::cout << f;
		bob.signForm(f);
		std::cout << f;
	}

	{
		std::cout << "\n=== signForm success message ===" << '\n';
		Bureaucrat alice("Alice", 1);
		Form f("TopSecret", 10, 5);
		alice.signForm(f);
	}

	{
		std::cout << "\n=== signForm failure message ===" << '\n';
		Bureaucrat alice("Alice", 100);
		Form f("TopSecret", 10, 5);
		alice.signForm(f);
	}

	{
		std::cout << "\n=== Form starts unsigned ===" << '\n';
		Form f("FreshForm", 75, 50);
		std::cout << "Is signed: " << (f.getSigned() ? "yes" : "no") << '\n';
	}

	{
		std::cout << "\n=== Form copy constructor ===" << '\n';
		Form original("Original", 30, 15);
		Bureaucrat bob("Bob", 20);
		bob.signForm(original);
		Form copy(original);
		std::cout << "Original: " << original;
		std::cout << "Copy: " << copy;
	}

	{
		std::cout << "\n=== Form copy assignment ===" << '\n';
		Form a("FormA", 50, 25);
		Form b("FormB", 100, 75);
		Bureaucrat bob("Bob", 30);
		bob.signForm(a);
		b = a;
		std::cout << "After assignment:" << '\n';
		std::cout << "a: " << a;
		std::cout << "b: " << b;
	}

	{
		std::cout << "\n=== operator<< output ===" << '\n';
		Form f("DisplayForm", 42, 21);
		std::cout << f;
	}

	{
		std::cout << "\n=== Bureaucrat regression ===" << '\n';
		Bureaucrat a("Steve", 75);
		std::cout << a;
		a.incrementGrade();
		std::cout << "after increment: " << a;
		a.decrementGrade();
		std::cout << "after decrement: " << a;
	}

	return 0;
}
