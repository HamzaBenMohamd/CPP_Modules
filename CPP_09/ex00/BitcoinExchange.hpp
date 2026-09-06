#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <stdexcept>
# include <cstdlib>
# include <cctype>

class BitcoinExchange 
{
    private:
        std::map<std::string, float> _database;

        void loadDatabase();
        bool isValidDate(const std::string &date) const;
        bool isValidValue(const std::string &valueStr, float &value) const;
        void processLine(const std::string &line);
        static std::string trim(const std::string &s);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void processInputFile(const std::string &filename);
};

#endif
