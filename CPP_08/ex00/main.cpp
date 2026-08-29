#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "easyfind.hpp"

template <typename T>
void testFind(T &container, int value, const char *label)
{
    try
    {
        typename T::iterator it = easyfind(container, value);
        std::cout << label << ": found " << *it << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << label << ": exception -> " << e.what() << "\n";
    }
}

int main()
{
    std::cout << "=== Vector: valid / missing values ===" << std::endl;

    std::vector<int> vect;
    vect.push_back(10);
    vect.push_back(20);
    vect.push_back(42);
    vect.push_back(1337);

    testFind(vect, 42, "vector (42)");
    testFind(vect, 999, "vector (999)");

    std::cout << "\n=== Vector: duplicate values -> first occurrence ===" << std::endl;

    std::vector<int> dup;
    dup.push_back(5);
    dup.push_back(7);
    dup.push_back(5);
    dup.push_back(9);

    std::vector<int>::iterator dupIt = easyfind(dup, 5);
    if (dupIt == dup.begin())
        std::cout << "vector duplicates: first occurrence is begin() -> OK\n";
    else
        std::cout << "vector duplicates: BUG, expected first occurrence at begin()\n";

    std::cout << "\n=== List: valid / missing values ===" << std::endl;

    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);

    testFind(lst, 3, "list (3)");

    testFind(lst, 100, "list (100)");

    std::cout << "\n=== List: duplicate values -> first occurrence ===" << std::endl;

    std::list<int> listDup;
    listDup.push_back(8);
    listDup.push_back(3);
    listDup.push_back(8);

    std::list<int>::iterator ld = easyfind(listDup, 8);
    if (ld == listDup.begin())
        std::cout << "list duplicates: first occurrence is begin() -> OK\n";
    else
        std::cout << "list duplicates: BUG, expected first occurrence at begin()\n";

    std::cout << "\n=== Empty container ===" << std::endl;

    std::vector<int> empty;
    try
    {
        easyfind(empty, 1);
        std::cout << "empty vector: BUG, no exception thrown\n";
    }
    catch (const std::exception &e)
    {
        if (std::string(e.what()) == "Value not found in container")
            std::cout << "empty vector: exception with expected message -> OK\n";
        else
            std::cout << "empty vector: unexpected message -> " << e.what() << "\n";
    }

    std::cout << "\n=== Const container (const overload) ===" << std::endl;

    const std::vector<int> constVect = vect;
    try
    {
        std::vector<int>::const_iterator cit = easyfind(constVect, 1337);
        if (cit != constVect.end())
            std::cout << "const vector (1337): found " << *cit << " via const_iterator\n";
        else
            std::cout << "const vector (1337): BUG, not found\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "const vector (1337): exception -> " << e.what() << "\n";
    }

    try
    {
        easyfind(constVect, -1);
        std::cout << "const vector (-1): BUG, no exception thrown\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "const vector (-1): exception -> " << e.what() << "\n";
    }

    std::cout << std::endl;
    return 0;
}
