#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

//? Randomly instantiates A, B, or C and returns it as a Base pointer
Base * generate(void)
{
    int random_choice = std::rand() % 3;

    switch (random_choice)
    {
        case 0:
            std::cout << "Generated: A\n";
            return new A();
        case 1:
            std::cout << "Generated: B\n";
            return new B();
        case 2:
            std::cout << "Generated: C\n";
            return new C();
        default:
            return NULL;
    }
}

//? Identifies the true type of the object using pointers
void identify(Base* p)
{
    if (p == NULL)
    {
        std::cout << "Error: Pointer is NULL\n";
        return;
    }

    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C\n";
    else
        std::cout << "Unknown type\n";
}

//? Identifies the true type of the object using references
void identify(Base &p)
{
    try
    {
        A &a = dynamic_cast<A&>(p);
        std::cout << "A\n";
        (void)a;
        return; 
    }
    catch (const std::exception &e) 
    {
    }

    try
    {
        B &b = dynamic_cast<B&>(p);
        std::cout << "B\n";
        (void)b;
        return;
    }
    catch (const std::exception &e) 
    {
    }

    try
    {
        C &c = dynamic_cast<C&>(p);
        std::cout << "C\n";
        (void)c;
        return;
    }
    catch (const std::exception &e) 
    {
    }

    std::cout << "Error: Unknown type\n";
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "--- Test 1 ---\n";
    Base *mystery1 = generate();
    std::cout << "Pointer identify: ";
    identify(mystery1);
    std::cout << "Reference identify: ";
    identify(*mystery1);
    delete mystery1;

    std::cout << "\n--- Test 2 ---\n";
    Base *mystery2 = generate();
    std::cout << "Pointer identify: ";
    identify(mystery2);
    std::cout << "Reference identify: ";
    identify(*mystery2);
    delete mystery2;

    std::cout << "\n--- Test 3 ---\n";
    Base *mystery3 = generate();
    std::cout << "Pointer identify: ";
    identify(mystery3);
    std::cout << "Reference identify: ";
    identify(*mystery3);
    delete mystery3;

    return 0;
}
