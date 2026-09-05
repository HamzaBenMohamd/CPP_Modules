#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <stdexcept>
# include <string>
# include <cctype>
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <sstream>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _rates;

        static int parseDate(const std::string &line, std::string &date, std::string &value);
        static bool isValidDate(const std::string &date);
        float getRate(const std::string &date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void loadDatabase(const std::string &dbFile);
        void processFile(const std::string &inputFile) const;
};

#endif
