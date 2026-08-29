#ifndef SPANEXCEPTIONS_HPP
#define SPANEXCEPTIONS_HPP

#include <exception>

class SpanFullException : public std::exception
{
    public:
        const char *what() const throw();
};

class SpanTooShortException : public std::exception
{
    public:
        const char *what() const throw();
};

#endif
