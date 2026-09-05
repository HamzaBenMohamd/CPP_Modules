#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    try
    {
        btc.loadDatabase("data.csv");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    // 10 significant digits: precise enough to clearly compare with the
    // database while still trimming trailing zeros (e.g. "0.9").
    std::cout << std::setprecision(10);

    btc.processFile(argv[1]);
    return 0;
}