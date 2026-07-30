#ifndef PresidentialPardonForm_HPP
# define PresidentialPardonForm_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include "AForm.hpp"
# include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string _target;

    public:
        PresidentialPardonForm();
        PresidentialPardonForm(std::string target);
        PresidentialPardonForm(const PresidentialPardonForm &copy);
        PresidentialPardonForm &operator=(const PresidentialPardonForm &assign);
        ~PresidentialPardonForm();

        void execute(Bureaucrat const & executor) const;
};

#endif
