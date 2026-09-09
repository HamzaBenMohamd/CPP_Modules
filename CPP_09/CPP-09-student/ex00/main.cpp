
#include "BitcoinExchange.hpp"

int main( int ac, char **av ) {
    
    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return -1;
    }

    std::ifstream dbFile("data.csv");
    std::ifstream inpFile(av[1]);

    myMap db;
    myMap input;

    try {
        processData(dbFile, db, ',', db);
        processData(inpFile, input, '|', db);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    inpFile.close();
    return 0;
}

