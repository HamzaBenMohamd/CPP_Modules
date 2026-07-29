#ifndef Intern_HPP
# define Intern_HPP

# include <iostream>
# include <string>
# include "AForm.hpp"
# include "Bureaucrat.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class Intern
{
    private:
        AForm *makeShrubbery(std::string target);
        AForm *makeRobotomy(std::string target);
        AForm *makePardon(std::string target);

    public:
        Intern();
        Intern(const Intern &copy);
        Intern &operator=(const Intern &assign);
        ~Intern();

        AForm* makeForm(std::string formName, std::string target);
};

#endif
