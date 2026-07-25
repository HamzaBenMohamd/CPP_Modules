#ifndef Form_HPP
# define Form_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
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

		Form();
		Form(std::string name, int gradeSign, int gradeExec);
		Form(const Form &copy);
		Form &operator=(const Form &assign);
		~Form();

		const std::string& getName() const;
		int getGradeSign() const;
		int getGradeExec() const;
		bool getSigned() const;

		void beSigned(const Bureaucrat &bureaucrat);
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
