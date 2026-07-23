#ifndef BUREAUCRAT_HPP
// ^ include guard: prevents the header from being included more than once in the same
//   translation unit. Without it, double inclusion would cause redefinition errors.
# define BUREAUCRAT_HPP

# include <iostream>
// ^ provides std::ostream for the operator<< overload. iostream is included rather than
//   ostream alone because downstream code often needs both input and output streams.
# include <string>
// ^ provides std::string for the _name attribute. We #include the header for the type
//   we actually use, so this header is self-sufficient (no missing-dependency errors for
//   users of Bureaucrat.hpp).
# include <stdexcept>
// ^ provides std::exception, the base class for our custom exception types. Inheriting
//   from std::exception ensures our exceptions are catchable as std::exception&,
//   which is a requirement in the subject.

class Bureaucrat
{
	private:
		const std::string   _name;
		// ^ const: the subject requires a "constant name". Once constructed, the name
		//   must never change. Making it const enforces this at compile time — any
		//   attempt to assign to _name will not compile. The trade-off is that the copy
		//   assignment operator cannot copy _name (const members are not assignable),
		//   which is correct: a Bureaucrat's identity (name) should be fixed for its
		//   lifetime.
		int                 _grade;
		// ^ subject requirement: grade ranges from 1 (highest) to 150 (lowest). Stored
		//   as a plain int. Validation happens in the constructor and in increment/decrement.

	public:
		class GradeTooHighException: public std::exception
		// ^ nested exception class. The subject demands Bureaucrat::GradeTooHighException
		//   so the exception name is scoped inside the class for clarity and encapsulation.
		{
			public:
				const char* what() const throw();
				// ^ override of std::exception::what(). The throw() (dynamic exception
				//   specification) is the C++98 way of saying "this function does not throw".
				//   Returns a C-string description of the error. We keep it as a declaration
				//   here and define it in the .cpp to avoid implementing functions in headers
				//   (which would earn a grade of 0 per the subject rules).
		};
		class GradeTooLowException: public std::exception
		// ^ symmetric to GradeTooHighException, for grades above 150.
		{
			public:
				const char* what() const throw();
		};

		// --- Orthodox Canonical Form (OCF) ---
		// The subject requires every non-interface class to follow OCF from Module 02 onward.
		// OCF consists of: default constructor, copy constructor, copy assignment operator,
		// destructor. These four ensure objects are created, copied, assigned, and destroyed
		// correctly. Exception classes are explicitly exempt from this requirement.
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &copy);
		Bureaucrat &operator=(const Bureaucrat &assign);
		~Bureaucrat();

		// getters (subject requirement):
		std::string getName() const;
		int getGrade() const;
		// ^ const qualifier: these functions do not modify the object. Marking them const
		//   allows calling them on const Bureaucrat references (e.g. in operator<< which
		//   takes a const reference).

		// Action Methods (subject requirement):
		void incrementGrade();
		void decrementGrade();
		// ^ the subject mandates two member functions to increment/decrement the grade.
		//   They throw GradeTooHighException or GradeTooLowException when the resulting
		//   grade goes out of range. "Increment" here means making the grade numerically
		//   smaller (grade 3 -> grade 2 = higher rank), which is counterintuitive but
		//   matches the subject's example: "incrementing a grade 3 should give you grade 2".
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);
// ^ non-member function overload of the insertion operator. The subject requires a <<
//   overload for Bureaucrat. It cannot be a member function because the left operand
//   would need to be a Bureaucrat object (not an ostream). As a free function,
//   it allows: std::cout << myBureaucrat;
//   This is the standard C++ idiom for output streaming.

#endif
