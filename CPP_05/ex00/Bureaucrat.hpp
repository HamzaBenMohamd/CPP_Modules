#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <stdexcept>

class Bureaucrat
{
	private:
		const std::string   _name;
		int                 _grade;

	public:
		class GradeTooHighException: public std::exception
		{
			public:
				const char* what() const throw();
		};
		class GradeTooLowException: public std::exception
		{
			public:
				const char* what() const throw();
		};

		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &copy);
		Bureaucrat &operator=(const Bureaucrat &assign);
		~Bureaucrat();

		//? getters:
		std::string getName() const;
		int getGrade() const;

		//? Action Methods:
		void incrementGrade();
		void decrementGrade();
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);

#endif
