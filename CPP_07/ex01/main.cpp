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
    std::cout << "--- Test 1: Array of Integers ---\n";
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intLen = sizeof(intArray) / sizeof(intArray[0]);

    std::cout << "Original: ";
    iter(intArray, intLen, printElement<int>);
    std::cout << "\n";

    std::cout << "Modified (incremented): ";
    iter(intArray, intLen, increment);
    iter(intArray, intLen, printElement<int>);
    std::cout << "\n\n";

    std::cout << "--- Test 2: Array of Strings ---\n";
    std::string strArray[] = {"Hello", "1337", "Templates", "Are", "Cool"};
    size_t strLen = sizeof(strArray) / sizeof(strArray[0]);

    iter(strArray, strLen, printElement<std::string>);
    std::cout << "\n\n";

    std::cout << "--- Test 3: Const Array ---\n";
    const int constArray[] = {42, 21, 1337};
    size_t constLen = sizeof(constArray) / sizeof(constArray[0]);

    iter(constArray, constLen, printElement<int>);
    std::cout << "\n";

    return 0;
}
