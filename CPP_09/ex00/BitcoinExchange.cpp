#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

/*
** ---------------------------------------------------------------------------
** Canonical Form
** ---------------------------------------------------------------------------
** These special member functions give the class the "Orthodox Canonical Form"
** required by the module. The map member is copied automatically by the
** compiler-generated copy operations, but we still define them explicitly.
** ---------------------------------------------------------------------------
*/
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _rates(other._rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        this->_rates = other._rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/*
** ---------------------------------------------------------------------------
** loadDatabase
** ---------------------------------------------------------------------------
** Reads the CSV file (format: "date,exchange_rate") and fills the map.
** The first line is a header and is skipped. Any malformed line is skipped
** so the rest of the database can still be loaded.
** ---------------------------------------------------------------------------
*/
void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
    std::ifstream file(dbFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    bool first = true;
    while (std::getline(file, line))
    {
        // Skip the header line ("date,exchange_rate").
        if (first)
        {
            first = false;
            continue;
        }
        // Skip empty lines / whitespace-only lines.
        if (line.find_first_not_of(" \t\r") == std::string::npos)
            continue;

        // The CSV is "date,rate". Split on the first comma.
        std::string::size_type comma = line.find(',');
        if (comma == std::string::npos)
            continue;

        std::string date = line.substr(0, comma);
        std::string rateStr = line.substr(comma + 1);

        // Basic sanity checks on the date and rate before inserting.
        if (!isValidDate(date))
            continue;

        std::istringstream iss(rateStr);
        float rate;
        if (!(iss >> rate) || rate < 0)
            continue;

        // insert: a later duplicate simply does not override the first value.
        _rates.insert(std::make_pair(date, rate));
    }

    if (_rates.empty())
        throw std::runtime_error("Error: empty or invalid database.");
}

/*
** ---------------------------------------------------------------------------
** processFile
** ---------------------------------------------------------------------------
** Reads the input file line by line. Every line must follow
** "date | value". For each line we either print the computed result
** or an appropriate error message. The program must NOT stop on the
** first error: the whole file is always processed.
** ---------------------------------------------------------------------------
*/
void BitcoinExchange::processFile(const std::string& inputFile) const
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // The database has no entry before 2009-01-02, so this is the
        // earliest date we can ever resolve a rate for.
        static const std::string MIN_DATE = "2009-01-02";

        std::string date, valueStr;
        int ret = parseDate(line, date, valueStr);

        // The first line "date | value" is a header: skip it silently.
        if (ret == 0 && date == "date" && valueStr == "value")
            continue;

        // Validate the date part (format + real calendar date).
        if (ret != 0 || !isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (date < MIN_DATE)
        {
            // No database entry exists at or before this date.
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Validate the value: must be a float or positive integer, >= 0.
        if (valueStr.find('-') != std::string::npos)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        char* end = NULL;
        double value = std::strtod(valueStr.c_str(), &end);
        // Reject if nothing was parsed, trailing junk, or a non-number.
        if (end == valueStr.c_str() || *end != '\0' || !std::isdigit(valueStr[0]))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Value must be between 0 and 1000 inclusive.
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        // Looks good: compute value * rate for the given date.
        float rate = getRate(date);
        std::cout << date << " => " << valueStr << " = "
                  << value * rate << std::endl;
    }
}

/*
** ---------------------------------------------------------------------------
** parseDate and isValidDate
** ---------------------------------------------------------------------------
** parseDate splits a line around the " | " separator. If the separator is
** missing or the date/value tokens are empty it returns -1.
**
** isValidDate checks that a string is a valid calendar date (YYYY-MM-DD):
**   - exactly 10 characters,
**   - digits and '-' in the right places,
**   - month between 01 and 12,
**   - day between 01 and 28/29/30/31 depending on the month and leap years.
** ---------------------------------------------------------------------------
*/
int BitcoinExchange::parseDate(const std::string& line, std::string& date,
                               std::string& value)
{
    // Locate the " | " separator. strlen(" | ") == 3.
    std::string::size_type sep = line.find(" | ");
    if (sep == std::string::npos)
        return -1;

    date = line.substr(0, sep);
    value = line.substr(sep + 3);

    // Neither side may be empty.
    if (date.empty() || value.empty())
        return -1;

    return 0;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    // Must be exactly "YYYY-MM-DD" -> 10 characters.
    if (date.length() != 10)
        return false;

    // Digits and dashes must be at the expected positions.
    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return false;
        }
        else if (!std::isdigit(date[i]))
            return false;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    // Month must be 1..12.
    if (month < 1 || month > 12)
        return false;

    // Days per month for a non-leap year.
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    // February has 29 days on leap years.
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && leap)
        maxDay = 29;

    return day >= 1 && day <= maxDay;
}

/*
** ---------------------------------------------------------------------------
** getRate
** ---------------------------------------------------------------------------
** Returns the rate stored for the exact date if it exists; otherwise it
** returns the rate of the closest date that is LOWER than the requested
** date (never a higher one, as the subject requires).
**
** This works because std::map keeps keys sorted. lower_bound(key) returns an
** iterator to the first element whose key is >= key. If it points past the
** end then every date is lower -> we take the last element. Otherwise we
** step back one position to get the nearest strictly-lower date.
** ---------------------------------------------------------------------------
*/
float BitcoinExchange::getRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _rates.lower_bound(date);

    // Every stored date is older than the requested one -> take the newest one.
    if (it == _rates.end())
        return _rates.rbegin()->second;

    // Exact match -> use it directly.
    if (it->first == date)
        return it->second;

    // Otherwise use the previous (nearest lower) date.
    if (it == _rates.begin())
        return 0.0f;    // Should not happen because of the MIN_DATE check.
    --it;
    return it->second;
}
