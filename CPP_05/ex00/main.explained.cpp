#include "Bureaucrat.hpp"
// ^ includes the Bureaucrat class definition so we can instantiate and manipulate
//   Bureaucrat objects. The test program must demonstrate that all functionality works.

int main()
// ^ the subject requires "a main function that contains enough tests to prove the
//   program works as expected." Without it, the exercise cannot be graded.
{
	// Test 1: Default Constructor
	// Purpose: verify that a Bureaucrat can be created with no arguments.
	// The default constructor should initialize with valid default values.
	{
		std::cout << "\033[31m==== Test Default Constructor ====\033[0m\n";
		Bureaucrat a;
		std::cout << a;
		// ^ operator<< is called implicitly. Expected output:
		//   "Anonymous, bureaucrat grade 5."
	}

	// Test 2: Parameterized Constructor (valid grade)
	// Purpose: verify that a Bureaucrat can be created with a name and valid grade.
	{
		std::cout << "\n\033[31m==== Test Parameterized Constructor ====\033[0m\n";
		Bureaucrat a("victime", 10);
		std::cout << a;
		// ^ Expected output: "victime, bureaucrat grade 10."
	}

	// Test 3: GradeTooHighException
	// Purpose: verify that creating a Bureaucrat with grade 0 (or negative) throws
	// GradeTooHighException. Grade 1 is the highest allowed, so 0 is out of range.
	// The exception must be catchable as std::exception& (subject requirement).
	{
		std::cout << "\n\033[31m==== Test GradeTooHighException ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 0);
			// ^ grade 0 is less than 1 => should throw GradeTooHighException
		}
		catch(const std::exception& e)
		// ^ catching by std::exception& proves that our exception inherits from
		//   std::exception, as the subject requires.
		{
			std::cout << e.what() << '\n';
			// ^ Expected output: "Too High grade!"
		}
	}

	// Test 4: GradeTooLowException
	// Purpose: verify that creating a Bureaucrat with grade 151 (or higher) throws
	// GradeTooLowException. Grade 150 is the lowest allowed.
	{
		std::cout << "\n\033[31m==== Test GradeTooLowException ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 151);
			// ^ grade 151 is greater than 150 => should throw GradeTooLowException
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
			// ^ Expected output: "Too Low grade!"
		}
		// Note: when the constructor throws, the destructor is NOT called because
		// the object never fully completed construction (C++ rule for exceptions in
		// constructors).
	}

	// Test 5: incrementGrade() at the upper bound
	// Purpose: verify that incrementing a Bureaucrat at grade 1 throws
	// GradeTooHighException. Grade 1 is the ceiling; no higher rank exists.
	{
		std::cout << "\n\033[31m==== Test incrementGrade() ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 1);
			a.incrementGrade();
			// ^ grade is 1, cannot increment higher => should throw
			//   GradeTooHighException
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		// Note: the destructor runs BEFORE the catch block because the throw happens
		// inside the try block; stack unwinding destroys 'a' as the exception propagates.
	}

	// Test 6: decrementGrade() at the lower bound
	// Purpose: verify that decrementing a Bureaucrat at grade 150 throws
	// GradeTooLowException. Grade 150 is the floor; no lower rank exists.
	{
		std::cout << "\n\033[31m==== Test decrementGrade() ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 150);
			a.decrementGrade();
			// ^ grade is 150, cannot decrement lower => should throw
			//   GradeTooLowException
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	// Test 7: Normal increment + decrement cycle
	// Purpose: verify that increment and decrement work correctly within valid range.
	// increment grade 75 -> 74 (higher rank), decrement -> 75 (back to original).
	// The subject states: "incrementing a grade 3 should result in a grade 2".
	{
		std::cout << "\n\033[31m==== Test increment + decrement ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 75);
			std::cout << "before increment: " << a;
			a.incrementGrade();
			std::cout << "after increment: " << a; // 75 -> 74
			a.decrementGrade();
			std::cout << "after decrement: " << a; // 74 -> 75
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	// Test 8: Copy Constructor
	// Purpose: verify that copying a Bureaucrat creates an independent duplicate.
	// This also implicitly tests that Bureaucrat is in Orthodox Canonical Form.
	{
		std::cout << "\n\033[31m==== Test Copy Constructor ====\033[0m\n";
		try
		{
			Bureaucrat a("victime", 15);
			Bureaucrat b(a);
			// ^ copy construction. b should be a copy of a with the same name and grade.
			std::cout << "'a' obj => " << a;
			std::cout << "'b' obj => " << b;
			// ^ both should show: "victime, bureaucrat grade 15."
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}

	return 0;
	// ^ EXIT_SUCCESS. An explicit return is good practice even though main() implicitly
	//   returns 0 in C++.
}
