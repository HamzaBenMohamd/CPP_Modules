#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <stdexcept>
#include <string>

/*
** BitcoinExchange class
**
** This class is responsible for:
**   - Loading the CSV database of bitcoin prices over time (date -> rate).
**   - Reading an input file containing "date | value" lines.
**   - For each valid line, outputting value * rate for the given date.
**
** It uses a std::map<std::string, float> as its container because a map
** keeps its keys (the dates) sorted. This ordering lets us easily find the
** "nearest lower date" required by the subject using lower_bound().
**
** Named after the class name -> BitcoinExchange.{cpp,hpp} as required.
*/
class BitcoinExchange
{
    public:
        BitcoinExchange();                          // Orthodox Canonical Form
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        // Loads the CSV database into the map. Throws on failure.
        void    loadDatabase(const std::string& dbFile);
        // Processes a whole input file, printing each result or an error.
        void    processFile(const std::string& inputFile) const;

    private:
        std::map<std::string, float> _rates;        // date -> exchange rate

        // Parses "date | value" style lines.
        static int  parseDate(const std::string& line, std::string& date,
                              std::string& value);
        // Validates that a date string is a real YYYY-MM-DD calendar date.
        static bool isValidDate(const std::string& date);
        // Returns the rate for the date or the nearest lower one.
        float       getRate(const std::string& date) const;
};

#endif
