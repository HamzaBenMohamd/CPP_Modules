#include <iostream>
#include <string>
#include <list>
#include "Span.hpp"

int main()
{
    // ---------------------------------------------------------------
    // Subject example: 5 numbers stored, expects shortestSpan == 2 and
    // longestSpan == 14 (sorts {3,6,9,11,17} internally).
    // ---------------------------------------------------------------
    std::cout << "=== Subject example: span of 5 ===\n";
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << "shortestSpan: " << sp.shortestSpan() << " (expected 2)\n";
    std::cout << "longestSpan: " << sp.longestSpan() << " (expected 14)\n";

    // ---------------------------------------------------------------
    // Capacity check: adding a 6th number to a Span(5) must throw.
    // We also verify the exception message so we know it's the right one.
    // ---------------------------------------------------------------
    std::cout << "\n=== addNumber when full throws ===\n";
    try
    {
        sp.addNumber(42);
        std::cout << "BUG: no exception thrown\n";
    }
    catch (const std::exception &e)
    {
        if (std::string(e.what()) == "Span is full")
            std::cout << "threw SpanFullException -> ok: " << e.what() << "\n";
        else
            std::cout << "unexpected message: " << e.what() << "\n";
    }

    // ---------------------------------------------------------------
    // Edge case: with 0 stored numbers neither span can be computed.
    // ---------------------------------------------------------------
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
            std::cout << "shortestSpan on empty -> ok: " << e.what() << "\n";
        }
        try
        {
            empty.longestSpan();
            std::cout << "longestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "longestSpan on empty -> ok: " << e.what() << "\n";
        }
    }

    // ---------------------------------------------------------------
    // Edge case: with only 1 stored number there is no pair to measure.
    // ---------------------------------------------------------------
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
            std::cout << "shortestSpan on single -> ok: " << e.what() << "\n";
        }
        try
        {
            single.longestSpan();
            std::cout << "longestSpan: BUG no exception\n";
        }
        catch (const std::exception &e)
        {
            std::cout << "longestSpan on single -> ok: " << e.what() << "\n";
        }
    }

    // ---------------------------------------------------------------
    // Values are stored as int, so negatives must be handled too.
    // {-5, 0, 3, 10}: closest diff is 3, overall range is 15.
    // ---------------------------------------------------------------
    std::cout << "\n=== Negative values (int storage) ===\n";
    Span neg(4);
    neg.addNumber(-5);
    neg.addNumber(0);
    neg.addNumber(3);
    neg.addNumber(10);
    std::cout << "neg shortestSpan: " << neg.shortestSpan() << " (expected 3)\n";
    std::cout << "neg longestSpan: " << neg.longestSpan() << " (expected 15)\n";

    // ---------------------------------------------------------------
    // Duplicates: an equal pair gives a shortest span of 0, and the
    // longest only cares about min and max (3..9 -> 6).
    // ---------------------------------------------------------------
    std::cout << "\n=== Duplicates: shortest 0, longest 6 ===\n";
    Span dup(10);
    dup.addNumber(5);
    dup.addNumber(5);
    dup.addNumber(9);
    dup.addNumber(3);
    std::cout << "duplicates shortestSpan: " << dup.shortestSpan() << " (expected 0)\n";
    std::cout << "duplicates longestSpan: " << dup.longestSpan() << " (expected 6)\n";

    // ---------------------------------------------------------------
    // Bulk fill: addRange() takes a range of iterators (here a std::list)
    // instead of many addNumber() calls. Values are {0, 3, 6, 9, 12}.
    // ---------------------------------------------------------------
    std::cout << "\n=== addRange from a std::list ===\n";
    Span rangeSpan(10);
    std::list<int> lst;
    for (int i = 0; i < 5; ++i)
        lst.push_back(i * 3);
    rangeSpan.addRange(lst.begin(), lst.end());
    std::cout << "rangeSpan size: " << rangeSpan.size() << " (expected 5)\n";
    std::cout << "rangeSpan shortestSpan: " << rangeSpan.shortestSpan() << " (expected 3)\n";
    std::cout << "rangeSpan longestSpan: " << rangeSpan.longestSpan() << " (expected 12)\n";

    // ---------------------------------------------------------------
    // addRange must also respect the capacity: filling a Span(3) with 10
    // values throws as soon as the span becomes full.
    // ---------------------------------------------------------------
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
        if (std::string(e.what()) == "Span is full")
            std::cout << "addRange overflow -> ok: " << e.what() << "\n";
        else
            std::cout << "addRange: unexpected message: " << e.what() << "\n";
    }

    // ---------------------------------------------------------------
    // Stress test: the subject asks to test with at least 10k numbers.
    // We fill 100,000 consecutive values via addRange: shortest == 1,
    // longest == 99999.
    // ---------------------------------------------------------------
    std::cout << "\n=== 100,000 numbers (subject requires >= 10,000) ===\n";
    const int count = 100000;
    Span big(static_cast<unsigned int>(count));
    std::vector<int> numbers;
    for (int i = 0; i < count; ++i)
        numbers.push_back(i);
    big.addRange(numbers.begin(), numbers.end());
    std::cout << "big size: " << big.size() << " (expected 100000)\n";
    std::cout << "big shortestSpan: " << big.shortestSpan() << " (expected 1)\n";
    std::cout << "big longestSpan: " << big.longestSpan() << " (expected 99999)\n";

    // ---------------------------------------------------------------
    // Copying and assigning a Span must carry over both the values and
    // the capacity, and the copy stays fully usable.
    // ---------------------------------------------------------------
    std::cout << "\n=== Copy constructor and copy assignment ===\n";
    Span copy(sp);
    std::cout << "copy shortestSpan: " << copy.shortestSpan() << " (expected 2)\n";
    Span assigned(1);
    assigned = sp;
    std::cout << "assigned longestSpan: " << assigned.longestSpan() << " (expected 14)\n";
    std::cout << "assigned size: " << assigned.size() << " (expected 5)\n";

    std::cout << "\nAll tests done.\n";
    return 0;
}