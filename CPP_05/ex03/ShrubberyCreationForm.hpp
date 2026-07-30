#ifndef ShrubberyCreationForm_HPP
# define ShrubberyCreationForm_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <fstream>
# include "AForm.hpp"
# include "Bureaucrat.hpp"

class ShrubberyCreationForm : public AForm
{
    private:
        std::string _target;

    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(std::string target);
        ShrubberyCreationForm(const ShrubberyCreationForm &copy);
        ShrubberyCreationForm &operator=(const ShrubberyCreationForm &assign);
        ~ShrubberyCreationForm();

        void execute(Bureaucrat const & executor) const;
};

#endif
