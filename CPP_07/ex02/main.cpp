#include <iostream> // std::cout
#include <string>   // std::string

#include "Array.hpp" // class template Array

// Test helper: prints every element of a const Array.
// Uses arr[i] (the CONST overload) and arr.size(), both declared const,
// so a const Array can be passed here.
template <typename T>
void printArray(const Array<T> &arr, const char *name)
{
    std::cout << name << " [size " << arr.size() << "]: ";
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main()
{
    // --- Test 1: empty array (default constructor) ---
    std::cout << "=== Test 1: empty array ===\n";
    Array<int> empty;
    std::cout << "size = " << empty.size() << std::endl; // must be 0
    // Accessing an empty array is out of bounds -> must throw.
    try
    {
        std::cout << empty[0] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "empty[0] threw an exception (expected)\n";
    }

    // --- Test 2: array of n default-initialized elements ---
    std::cout << "\n=== Test 2: default-initialized values ===\n";
    Array<int> ints(5);
    printArray(ints, "ints"); // ints are 0 because of new int[5]()
    // Writing through operator[] (non-const overload).
    for (unsigned int i = 0; i < ints.size(); i++)
        ints[i] = i * 10;
    printArray(ints, "ints after fill");

    // --- Test 3: deep copy (copy constructor) ---
    std::cout << "\n=== Test 3: copy constructor (deep copy) ===\n";
    Array<int> copy(ints);   // copy constructed
    printArray(copy, "copy");
    copy[0] = -1;            // modify ONLY the copy
    printArray(ints, "ints");  // original must be unchanged
    printArray(copy, "copy");

    // --- Test 4: deep copy (assignment operator) ---
    std::cout << "\n=== Test 4: assignment operator (deep copy) ===\n";
    Array<int> assigned(2);
    assigned = ints;         // replaces previous buffer
    printArray(assigned, "assigned");
    assigned[1] = -2;        // modify ONLY the assigned copy
    printArray(ints, "ints");
    printArray(assigned, "assigned");

    // --- Test 5: out-of-bounds access throws ---
    std::cout << "\n=== Test 5: out-of-bounds access ===\n";
    try
    {
        ints[100];           // valid array but index beyond size
    }
    catch (const std::exception &e)
    {
        std::cout << "ints[100] threw an exception (expected)\n";
    }

    // --- Test 6: complex type (std::string) ---
    std::cout << "\n=== Test 6: complex type (std::string) ===\n";
    Array<std::string> words(3);
    words[0] = "Hello";
    words[1] = "World";
    words[2] = "!";
    printArray(words, "words");

    // --- Test 7: const Array is read-only ---
    std::cout << "\n=== Test 7: const array ===\n";
    const Array<std::string> constWords = words; // copy of a string array
    printArray(constWords, "constWords");
    // constWords[0] = "x"; // would NOT compile: const overload returns const&

    return 0;
}
