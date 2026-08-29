#include <algorithm>
#include "Span.hpp"

Span::Span() : _numbers(), _size(0)
{
}

Span::Span(unsigned int n) : _numbers(), _size(n)
{
}

Span::Span(const Span &other) : _numbers(other._numbers), _size(other._size)
{
}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _numbers = other._numbers;
        _size = other._size;
    }
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int value)
{
    if (_numbers.size() >= _size)
        throw SpanFullException();
    _numbers.push_back(value);
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw SpanTooShortException();

    std::vector<int> sorted(_numbers);
    std::sort(sorted.begin(), sorted.end());

    unsigned int shortest = static_cast<unsigned int>(sorted[1] - sorted[0]);
    for (size_t i = 2; i < sorted.size(); ++i)
    {
        unsigned int diff = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
        if (diff < shortest)
            shortest = diff;
    }
    return shortest;
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw SpanTooShortException();

    std::vector<int>::const_iterator min = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator max = std::max_element(_numbers.begin(), _numbers.end());
    return static_cast<unsigned int>(*max - *min);
}

unsigned int Span::size() const
{
    return static_cast<unsigned int>(_numbers.size());
}
