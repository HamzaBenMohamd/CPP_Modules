#ifndef NOTFOUNDEXCEPTION_HPP
# define NOTFOUNDEXCEPTION_HPP

# include <exception>

class NotFoundException : public std::exception
{
    public:
        const char *what() const throw();
};

#endif

//! => If any non-interface class is not in orthodox canonical class form, do not grade this exercise.
