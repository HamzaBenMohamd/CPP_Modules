#include "Bureaucrat.hpp"
// ^ includes the class declaration so the compiler knows the layout of Bureaucrat and
//   its member types. "" (quotes) tells the preprocessor to look in the current directory
//   first, which is the standard practice for local project headers.

// =============================================================================
// Orthodox Canonical Form
// =============================================================================

// Default Constructor
Bureaucrat::Bureaucrat() : _name("Anonymous"), _grade(5)
// ^ initializer list: the only way to initialize const and reference members before the
//   constructor body runs. _name("Anonymous") gives a default name; _grade(5) is a
//   valid mid-range grade. The subject does not mandate a default constructor, but OCF
//   requires it, and it is useful for creating "empty" Bureaucrat objects (e.g. in arrays).
{
	std::cout << "Default Constructor called of Bureaucrat" << std::endl;
	// ^ diagnostic output for testing/demo purposes. Not required by the subject but
	//   helps trace object lifetimes.
}

// Parameterized Constructor
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
// ^ _name(name) uses the copy constructor of std::string to initialize the const member.
//   _grade is NOT initialized here because we validate the grade first.
{
	std::cout << "Default Parameters Constructor called of Bureaucrat" << std::endl;

	// Grade validation: the subject requires grades to be in [1, 150].
	// We check BEFORE assigning to prevent the object from existing in an invalid state.
	// If an exception is thrown here, the partially-constructed object's destructor is
	// NOT called (C++98 rule for objects that never fully completed construction).
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
		// ^ grade 0 or negative: too high (better than 1). The subject says grade 1 is
		//   the highest, so anything < 1 is invalid.
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
		// ^ grade 151 or above: too low (worse than 150).
	else
		this->_grade = grade;
		// ^ only assign once validation passes. The else branch ensures _grade is never
		//   left uninitialized for valid grades.
}

// Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat &copy) : _name(copy._name), _grade(copy._grade)
// ^ member-wise copy using initializer list. _name(copy._name) is valid because even
//   though _name is const, we are initializing it (not assigning). This is the only
//   way to "copy" a const member.
{
	std::cout << "Copy Constructor called of Bureaucrat" << std::endl;
}

// Destructor
Bureaucrat::~Bureaucrat()
// ^ called when a Bureaucrat object goes out of scope or is deleted. Since no dynamic
//   memory allocation is used (no new/malloc), no manual cleanup is needed. The destructor
//   still exists to satisfy OCF and to provide a place for future cleanup if needed.
{
	std::cout << "Destructor called of Bureaucrat" << std::endl;
}

// Copy Assignment Operator
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &assign)
// ^ assigns the contents of 'assign' to 'this'. Returns *this to support chained
//   assignment (a = b = c). The const _name member cannot be assigned to, which is
//   intentional: the subject says the name is constant, so it should not change after
//   construction. Only _grade is copied.
{
	std::cout << "Copy Assignment Operator called of Bureaucrat" << std::endl;
	if (this != &assign)
	// ^ self-assignment guard: prevents problems if someone writes a = a.
	//   Without this, we might decrement a reference count or free memory that we
	//   still need (though for ints it is harmless, it is good OCF practice).
	{
		this->_grade = assign._grade;
		// ^ _name is NOT copied because it is const. This is a deliberate design
		//   choice enforced by the subject's requirement for a constant name.
	}
	return (*this);
}

// =============================================================================
// Custom Exceptions
// =============================================================================

// Override of what() for GradeTooHighException
const char *Bureaucrat::GradeTooHighException::what() const throw()
// ^ throw() is the C++98 exception specification meaning "does not throw".
//   what() is called when catching the exception to get a human-readable message.
{
	return "Too High grade!";
	// ^ returned C-string. The caller must not free or modify it. This message is
	//   printed by the catch block in main.cpp.
}

// Override of what() for GradeTooLowException
const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Too Low grade!";
}

// =============================================================================
// Getters
// =============================================================================

std::string Bureaucrat::getName() const
// ^ returns the bureaucrat's name by value (copy). Returning by const reference
//   (const std::string&) would be more efficient but requires the caller to be
//   careful about lifetime. Returning by value is safe and simple.
{
	return this->_name;
}

int Bureaucrat::getGrade() const
// ^ returns the bureaucrat's grade. The const qualifier allows calling this on const
//   Bureaucrat references. Without it, operator<< (which takes const Bureaucrat&)
//   could not access _grade.
{
	return this->_grade;
}

// =============================================================================
// Action Methods
// =============================================================================

void Bureaucrat::incrementGrade()
// ^ "incrementing" the grade actually raises the bureaucrat's rank, making the
//   numerical grade smaller. The subject says: "incrementing a grade 3 should result
//   in a grade 2 for the bureaucrat." This is the key rule — higher rank = lower
//   number, which is the opposite of the intuitive direction.
{
	if (this->_grade <= 1)
	// ^ grade 1 is the highest possible. If we are already at 1, we cannot go higher.
	//   The condition uses <= 1 as a safety net (grade 0 should not exist, but if it
	//   somehow did, we would still catch it).
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
	// ^ numerically decrement to move toward 1 (higher rank).
	//   Example: grade 3 -> grade 2 after increment.
}

void Bureaucrat::decrementGrade()
// ^ "decrementing" lowers the bureaucrat's rank, making the numerical grade larger.
//   This is the opposite of incrementGrade().
{
	if (this->_grade >= 150)
	// ^ grade 150 is the lowest possible. If we are already at 150, we cannot go lower.
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
	// ^ numerically increment to move toward 150 (lower rank).
	//   Example: grade 149 -> grade 150 after decrement.
}

// =============================================================================
// Operator Overloads (non-member)
// =============================================================================

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat)
// ^ non-member overload of the insertion operator. The subject requires this exact
//   output format: <name>, bureaucrat grade <grade>.
//   Returns the ostream reference to allow chaining: std::cout << a << b;
//   The Bureaucrat parameter is const because printing does not modify the object.
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << '.' << '\n';
	// ^ the format matches the subject exactly:
	//   "<name>, bureaucrat grade <grade>."
	//   with a newline appended. The '.' is placed before the newline as required.
	return out;
}
