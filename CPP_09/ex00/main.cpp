#include "BitcoinExchange.hpp"

int main(int ac, char* av[])
{
    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    const char* dbFile = "data.csv";

    try
    {
        BitcoinExchange btc;
        btc.loadDatabase(dbFile);
        btc.processFile(av[1]);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
