#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

/*
** BitcoinExchange
**
** Loads a CSV database of bitcoin prices (date,exchange_rate) into a
** std::map<std::string, double> and evaluates, for every line of an input
** file ("date | value"), the value * rate for that date.
**
** A std::map is ordered by key, so lower_bound() cheaply finds the
** "nearest lower date" required by the subject.
**
** File names follow the class name -> BitcoinExchange.{cpp,hpp}.
*/
class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Loads the CSV database into the map. Throws on failure.
        void loadDatabase(const std::string& dbFile);

        // Processes a whole input file, printing each result or an error.
        void processFile(const std::string& inputFile) const;

    private:
        std::map<std::string, double> _rates;   // date -> exchange rate

        // Small static helpers (no instance state needed).
        static std::string trim(const std::string& s);
        static bool        splitOnChar(const std::string& line, char sep,
                                       std::string& left, std::string& right);
        static bool        parseDouble(const std::string& s, double& out);
        static bool        isValidDate(const std::string& date);
        static bool        isLeapYear(int year);

        // Rate for an exact date, or the nearest strictly-lower one.
        // Returns false when the date is older than every DB entry.
        bool getRate(const std::string& date, double& rate) const;
};

#endif