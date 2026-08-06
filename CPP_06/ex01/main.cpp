#include "Serializer.hpp"

int main()
{
    Data myData;
    myData.id    = 42;
    myData.name  = "Hello 1337!";
    myData.level = 4.2f;

    uintptr_t raw = Serializer::serialize(&myData);

    std::cout << "Original Data address: " << &myData << "\n";
    std::cout << "Serialized (uintptr_t): " << raw << "\n";

    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << "Deserialized address:  " << deserializedData << "\n\n";

    std::cout << "--- Verifying pointer ---\n";
    if (deserializedData == &myData)
        std::cout << "SUCCESS: deserialize(serialize(&myData)) == &myData\n\n";
    else
        std::cout << "FAIL: the pointers are different!\n\n";

    std::cout << "--- Verifying Data ---\n";
    std::cout << "ID:    " << deserializedData->id    << "\n";
    std::cout << "Name:  " << deserializedData->name  << "\n";
    std::cout << "Level: " << deserializedData->level << "\n";

    return 0;
}
