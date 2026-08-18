#include <iostream>
#include <string>
#include "Array.hpp"

template <typename DataType>
void printArray(const Array<DataType> &arr, const char *name)
{
    std::cout << name << " [size " << arr.size() << "]: ";
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== Test 1: empty array ===\n";
    Array<int> empty;
    std::cout << "size = " << empty.size() << std::endl;
    try
    {
        std::cout << empty[0] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "empty[0] threw an exception\n";
    }

    std::cout << "\n=== Test 2: default-initialized values ===\n";
    Array<int> ints(5);
    printArray(ints, "ints");
    for (unsigned int i = 0; i < ints.size(); i++)
        ints[i] = i * 10;
    printArray(ints, "ints after fill");

    std::cout << "\n=== Test 3: copy constructor (deep copy) ===\n";
    Array<int> copy(ints);
    printArray(copy, "copy");
    copy[0] = -1;
    printArray(ints, "ints");
    printArray(copy, "copy");

    std::cout << "\n=== Test 4: assignment operator (deep copy) ===\n";
    Array<int> assigned(2);
    printArray(assigned, "original assigned");
    assigned = ints;
    printArray(assigned, "assigned");
    assigned[1] = -2;
    printArray(ints, "ints");
    printArray(assigned, "assigned");

    std::cout << "\n=== Test 5: out-of-bounds access ===\n";
    try
    {
        ints[100];
    }
    catch (const std::exception &e)
    {
        std::cout << "ints[100] threw an exception\n";
    }

    std::cout << "\n=== Test 6: complex type (std::string) ===\n";
    Array<std::string> words(3);
    words[0] = "Hello";
    words[1] = "World";
    words[2] = "!";
    printArray(words, "words");

    std::cout << "\n=== Test 7: const array ===\n";
    const Array<std::string> constWords = words;
    printArray(constWords, "constWords");
    // constWords[1] = "1337"; // compile error

    return 0;
}
