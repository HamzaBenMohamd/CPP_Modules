#ifndef RobotomyRequestForm_HPP
# define RobotomyRequestForm_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include <cstdlib>
# include <ctime>
# include "AForm.hpp"
# include "Bureaucrat.hpp"

class RobotomyRequestForm : public AForm
{
    private:
        std::string _target;

    public:
        RobotomyRequestForm();
        RobotomyRequestForm(std::string target);
        RobotomyRequestForm(const RobotomyRequestForm &copy);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &assign);
        ~RobotomyRequestForm();

        void execute(Bureaucrat const & executor) const;
};

#endif
