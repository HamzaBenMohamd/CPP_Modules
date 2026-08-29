#include "SpanExceptions.hpp"

const char *SpanFullException::what() const throw()
{
    return "Span is full";
}

const char *SpanTooShortException::what() const throw()
{
    return "Not enough numbers to compute a span";
}
