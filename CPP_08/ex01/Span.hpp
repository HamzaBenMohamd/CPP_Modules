#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include "SpanExceptions.hpp"

class Span
{
    private:
        std::vector<int> _numbers;
        unsigned int _size;

    public:
        Span();
        Span(unsigned int n);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void addNumber(int value);
        unsigned int shortestSpan() const;
        unsigned int longestSpan() const;
        unsigned int size() const;

        template <typename Iterator>
        void addRange(Iterator begin, Iterator end)
        {
            for (Iterator it = begin; it != end; ++it)
                addNumber(*it);
        }
};

#endif
