#include <iostream>
#include <list>
#include <stack>
#include <string>
#include "MutantStack.hpp"

int main()
{
    // ---------------------------------------------------------------
    // Exact subject example: top -> 17, size -> 1, then the iteration
    // prints every element from bottom to top: 5 3 5 737 0.
    // ---------------------------------------------------------------
    std::cout << "=== Subject example (expect 17, 1, then 5 3 5 737 0) ===\n";
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    // A MutantStack must stay usable as a plain std::stack (inheritance).
    std::stack<int> s(mstack);
    std::cout << "std::stack copy size: " << s.size() << " (expected 5)\n";
    std::cout << "std::stack copy top: " << s.top() << " (expected 0)\n";

    // ---------------------------------------------------------------
    // The subject says the iteration output must be identical to a
    // std::list filled with the same operations (push == push_back,
    // pop == pop_back). Let's prove it programmatically.
    // ---------------------------------------------------------------
    std::cout << "\n=== Same iteration as std::list ===\n";
    MutantStack<int> ms;
    std::list<int> lst;

    ms.push(5);       lst.push_back(5);
    ms.push(17);      lst.push_back(17);
    ms.pop();         lst.pop_back();
    ms.push(3);       lst.push_back(3);
    ms.push(5);       lst.push_back(5);
    ms.push(737);     lst.push_back(737);
    ms.push(0);       lst.push_back(0);

    std::cout << "mutant top: " << ms.top() << " vs list back: " << lst.back() << "\n";
    std::cout << "mutant size: " << ms.size() << " vs list size: " << lst.size() << "\n";

    bool same = true;
    MutantStack<int>::iterator mit = ms.begin();
    std::list<int>::iterator lit = lst.begin();
    while (mit != ms.end() && lit != lst.end())
    {
        if (*mit != *lit)
        {
            same = false;
            break;
        }
        ++mit;
        ++lit;
    }
    if (mit != ms.end() || lit != lst.end())
        same = false;
    std::cout << (same ? "iteration matches std::list: OK"
                       : "iteration MISMATCHES std::list") << "\n";

    // ---------------------------------------------------------------
    // Reverse iterators: walk from the top back to the bottom.
    // ---------------------------------------------------------------
    std::cout << "\n=== Reverse iteration (expect 0 737 5 3 5) ===\n";
    MutantStack<int>::reverse_iterator rit = ms.rbegin();
    for (; rit != ms.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << "\n";

    // ---------------------------------------------------------------
    // Empty stack: begin() must equal end().
    // ---------------------------------------------------------------
    std::cout << "\n=== Empty stack iteration ===\n";
    MutantStack<int> empty;
    if (empty.begin() == empty.end())
        std::cout << "begin() == end() on empty stack: OK\n";
    else
        std::cout << "BUG: begin() != end() on empty stack\n";

    // ---------------------------------------------------------------
    // Copy constructor and copy assignment must produce independent,
    // fully iterable copies.
    // ---------------------------------------------------------------
    std::cout << "\n=== Copy ctor and assignment ===\n";
    MutantStack<int> copy(ms);
    MutantStack<int> assigned;
    assigned = ms;
    std::cout << "copy size: " << copy.size()
              << " assigned size: " << assigned.size() << " (expected 5 5)\n";
    MutantStack<int>::iterator cit = copy.begin();
    for (; cit != copy.end(); ++cit)
        std::cout << *cit << " ";
    std::cout << "\n";

    // ---------------------------------------------------------------
    // A const MutantStack uses const_iterator / const_reverse_iterator.
    // ---------------------------------------------------------------
    std::cout << "\n=== Const MutantStack ===\n";
    const MutantStack<int> cms = ms;
    MutantStack<int>::const_iterator cIt = cms.begin();
    MutantStack<int>::const_iterator cIte = cms.end();
    for (; cIt != cIte; ++cIt)
        std::cout << *cIt << " ";
    std::cout << "\n";
    MutantStack<int>::const_reverse_iterator crIt = cms.rbegin();
    std::cout << "const rbegin element: " << *crIt << " (expected 0)\n";

    // ---------------------------------------------------------------
    // The class is a template: any value type must work.
    // ---------------------------------------------------------------
    std::cout << "\n=== MutantStack<std::string> ===\n";
    MutantStack<std::string> words;
    words.push("hello");
    words.push("world");
    MutantStack<std::string>::iterator wit = words.begin();
    for (; wit != words.end(); ++wit)
        std::cout << *wit << " ";
    std::cout << "\ntop: " << words.top() << " (expected world)\n";

    // ---------------------------------------------------------------
    // Every original std::stack member (push/pop/top/size/empty) must
    // still behave as before.
    // ---------------------------------------------------------------
    std::cout << "\n=== std::stack interface preserved ===\n";
    std::cout << "empty() before push: " << (ms.empty() ? "true" : "false")
              << " (on ms with 5 elements, expected false)\n";
    ms.push(99);
    std::cout << "after push(99): top() = " << ms.top() << " (expected 99), ";
    std::cout << "size() = " << ms.size() << " (expected 6)\n";
    ms.pop();
    std::cout << "after pop(): top() = " << ms.top() << " (expected 0)\n";

    std::cout << "\nAll tests done.\n";
    return 0;
}
