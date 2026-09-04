#include <cstdlib>
#include <iostream>

#include "BitcoinExchange.hpp"

/*
** ---------------------------------------------------------------------------
** main
** ---------------------------------------------------------------------------
** Entry point of the "btc" program.
**
** The program takes exactly one argument: the input file (which contains the
** dates/values to evaluate). The database itself is the CSV file provided
** with the subject and is expected to be named "data.csv".
**
** Steps:
**   1. Check we have exactly one CLI argument, otherwise print usage.
**   2. Build the BitcoinExchange object and load the database.
**   3. Process the input file (prints results or errors).
** Exceptions thrown by the class (e.g. DB not opening) are caught here.
** ---------------------------------------------------------------------------
*/
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    // The CSV database shipped with the subject.
    const char* dbFile = "data.csv";

    try
    {
        BitcoinExchange btc;
        btc.loadDatabase(dbFile);
        btc.processFile(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
