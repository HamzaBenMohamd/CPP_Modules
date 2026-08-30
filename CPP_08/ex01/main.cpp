#include <iostream>
#include <string>
#include <list>
#include "Span.hpp"

int main()
{
    std::cout << "=== Subject example: span of 5 ===\n";
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << "shortestSpan: " << sp.shortestSpan() << "\n";
    std::cout << "longestSpan: " << sp.longestSpan() << "\n";

    std::cout << "\n=== addNumber when full throws ===\n";
    try
    {
        sp.addNumber(42);
        std::cout << "BUG: no exception thrown\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== Empty span: both span functions throw ===\n";
    {
        Span empty(5);
        try
        {
            empty.shortestSpan();
            std::cout << "shortestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
        try
        {
            empty.longestSpan();
            std::cout << "longestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "\n=== Single number: both span functions throw ===\n";
    {
        Span single(5);
        single.addNumber(7);
        try
        {
            single.shortestSpan();
            std::cout << "shortestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
        try
        {
            single.longestSpan();
            std::cout << "longestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    std::cout << "\n=== Negative values ===\n";
    Span neg(4);
    neg.addNumber(-5);
    neg.addNumber(0);
    neg.addNumber(3);
    neg.addNumber(10);
    std::cout << "shortestSpan: " << neg.shortestSpan() << "\n";
    std::cout << "longestSpan: " << neg.longestSpan() << "\n";

    std::cout << "\n=== Duplicates: shortest 0, longest 6 ===\n";
    Span dup(10);
    dup.addNumber(5);
    dup.addNumber(5);
    dup.addNumber(9);
    dup.addNumber(3);
    std::cout << "shortestSpan: " << dup.shortestSpan() << "\n";
    std::cout << "longestSpan: " << dup.longestSpan() << "\n";

    std::cout << "\n=== addRange from a std::list ===\n";
    Span rangeSpan(10);
    std::list<int> lst;
    for (int i = 0; i < 5; ++i)
        lst.push_back(i * 3);
    rangeSpan.addRange(lst.begin(), lst.end());
    std::cout << "rangeSpan size: " << rangeSpan.size() << "\n";
    std::cout << "rangeSpan shortestSpan: " << rangeSpan.shortestSpan() << "\n";
    std::cout << "rangeSpan longestSpan: " << rangeSpan.longestSpan() << "\n";

    std::cout << "\n=== addRange overflowing capacity throws ===\n";
    Span small(3);
    std::vector<int> tooMany;
    for (int i = 0; i < 10; ++i)
        tooMany.push_back(i);
    try
    {
        small.addRange(tooMany.begin(), tooMany.end());
        std::cout << "BUG: no exception thrown\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n=== 100,000 numbers (subject requires >= 10,000) ===\n";
    Span big(100000);
    std::vector<int> numbers;
    for (int i = 0; i < 100000; ++i)
        numbers.push_back(i);
    big.addRange(numbers.begin(), numbers.end());
    std::cout << "big size: " << big.size() << "\n";
    std::cout << "big shortestSpan: " << big.shortestSpan() << "\n";
    std::cout << "big longestSpan: " << big.longestSpan() << "\n";

    std::cout << "\n=== Copy constructor and copy assignment ===\n";
    Span copy(sp);
    std::cout << "copy shortestSpan: " << copy.shortestSpan() << "\n";
    Span assigned(1);
    assigned = sp;
    std::cout << "assigned longestSpan: " << assigned.longestSpan() << "\n";
    std::cout << "assigned size: " << assigned.size() << "\n";

    return 0;
}
