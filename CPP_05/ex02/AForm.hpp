#ifndef AForm_HPP
# define AForm_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    private:
        const std::string   _name;
        const int           _gradeSign;
        const int           _gradeExec;
        bool                _signed;

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
		class NotSignedException: public std::exception
		{
			public:
				const char* what() const throw();
		};

		AForm();
		AForm(std::string name, int gradeSign, int gradeExec);
		AForm(const AForm &copy);
		AForm &operator=(const AForm &assign);
		~AForm();

		const std::string& getName() const;
		int getGradeSign() const;
		int getGradeExec() const;
		bool getSigned() const;

		void beSigned(const Bureaucrat &bureaucrat);

		virtual void execute(Bureaucrat const & executor) const = 0;
	};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
