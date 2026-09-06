#include "BitcoinExchange.hpp"

//? Default Constructor
BitcoinExchange::BitcoinExchange()
{
    loadDatabase();
}

//? Copy Constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}

//? Assignment Operator
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other) 
    {
        this->_database = other._database;
    }
    return *this;
}

//? Destructor
BitcoinExchange::~BitcoinExchange() {}

//? load Data base file (data.csv)
void BitcoinExchange::loadDatabase()
{
    std::ifstream file("data.csv");
    if (!file.is_open()) 
        throw std::runtime_error("Error: could not open database file.");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = line.substr(0, commaPos);
            std::string rateStr = line.substr(commaPos + 1);
            char* endPtr;
            float rate = static_cast<float>(std::strtod(rateStr.c_str(), &endPtr));
            _database[date] = rate;
        }
    }
}

//? load input file from user (argv[1])
void BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file.\n";
        return ;
    }
    std::string line;
    bool isFirstLine = true;
    while (std::getline(file, line))
    {
        std::string trimmed = trim(line);
        if (trimmed.empty())
            continue;
        if (isFirstLine)
        {
            isFirstLine = false;
            if (trimmed == "date | value")
                continue;
        }
        processLine(trimmed);
    }
}

//? process one line of the input file: "date | value"
void BitcoinExchange::processLine(const std::string &line)
{
    size_t delimPos = line.find('|');
    if (delimPos == std::string::npos)
    {
        std::cout << "Error: bad input => " << line << '\n';
        return ;
    }
    std::string date = trim(line.substr(0, delimPos));
    std::string valueStr = trim(line.substr(delimPos + 1));
    if (date.empty() || valueStr.empty())
    {
        std::cout << "Error: bad input => " << line << '\n';
        return ;
    }
    float value;
    if (!isValidDate(date))
    {
        std::cout << "Error: bad input => " << date << '\n';
        return ;
    }
    if (!isValidValue(valueStr, value))
        return ;
    std::map<std::string, float>::iterator it = _database.lower_bound(date);

    if (it == _database.end() || it->first != date)
    {
        if (it == _database.begin())
        {
            std::cout << "Error: date is older than any database entry => " << date << '\n';
            return ;
        }
        --it;
    }
    float result = value * it->second;
    std::cout << date << " => " << value << " = " << result << '\n';
}

//? check if the input value is a valid number between 0 and 1000
bool BitcoinExchange::isValidValue(const std::string &valueStr, float &value) const
{
    char	*endPtr;
    double	parsedValue = std::strtod(valueStr.c_str(), &endPtr);
    if (valueStr.c_str() == endPtr || *endPtr != '\0')
    {
        std::cout << "Error: bad input => " << valueStr << '\n';
        return false;
    }
    if (parsedValue < 0)
    {
        std::cout << "Error: not a positive number.\n";
        return false;
    }
    if (parsedValue > 1000.0)
    {
        std::cout << "Error: too large a number.\n";
        return false;
    }
    value = static_cast<float>(parsedValue);
    return true;
}

//? check if the date is a real calendar date "YYYY-MM-DD" + handles leap years
bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[1] = 29;
    if (day > daysInMonth[month - 1])
        return false;
    return true;
}

//? trim: remove leading/trailing spaces and tabs from a string.
std::string BitcoinExchange::trim(const std::string &s)
{
    std::string::size_type start = s.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";
    std::string::size_type end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}
