#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(const T &element)
{
    std::cout << element << " ";
}

void increment(int &n)
{
    n++;
}

int main()
{
    // --- Test 1: non-const array, both read-only and modifying functions ---
    std::cout << "--- Test 1: Array of Integers ---\n";
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

    std::cout << "Original: ";
    // printElement<int> is an INSTANTIATED function template:
    // it selects the specialization void(const int&), then iter receives it.
    // T = int, F = void (*)(const int&). const int& accepts an int lvalue.
    ::iter(intArray, intLen, printElement<int>); //? how this fun get converted from T to its real version ( as a data type )
    std::cout << "\n";

    std::cout << "Modified (incremented): ";
    // increment takes int& (non-const): iter calls increment(array[i]).
    // T = int, F = void (*)(int&).
    ::iter(intArray, intLen, increment);
    ::iter(intArray, intLen, printElement<int>); // reprint to show the change
    std::cout << "\n\n";

    // --- Test 2: different element type (std::string) ---
    std::cout << "--- Test 2: Array of Strings ---\n";
    std::string strArray[] = {"Hello", "1337", "Templates", "Are", "Cool"};
    size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

    // Same iter template, reused for std::string: T = std::string.
    ::iter(strArray, strLen, printElement<std::string>);
    std::cout << "\n\n";

    // --- Test 3: CONST array ---
    // T is deduced as const int (from const int*), so func must accept
    // a const int&. printElement<int> does, hence this compiles.
    std::cout << "--- Test 3: Const Array ---\n";
    const int constArray[] = {42, 21, 84};
    size_t constLen = sizeof(constArray) / sizeof(constArray[0]);

    ::iter(constArray, constLen, printElement<int>);
    std::cout << "\n";

    return 0;
}
