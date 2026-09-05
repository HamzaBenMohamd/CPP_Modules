#include "BitcoinExchange.hpp"

/*
** ---------------------------------------------------------------------------
** Canonical Form
** ---------------------------------------------------------------------------
** Orthodox Canonical Form as required by the module. The std::map member is
** copied automatically by the compiler-generated operations, but we still
** define them explicitly for clarity.
** ---------------------------------------------------------------------------
*/
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _rates = other._rates;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/*
** ---------------------------------------------------------------------------
** loadDatabase
** ---------------------------------------------------------------------------
** Reads the CSV file (format: "date,exchange_rate") and fills the map.
**
** The first line must be the header; every following "date,rate" line is
** validated (real date + finite non-negative number) and inserted. Lines
** that fail validation are skipped so the rest of the DB still loads.
** If nothing can be loaded we throw so the caller reports the failure.
** ---------------------------------------------------------------------------
*/
void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
    std::ifstream file(dbFile.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    // First line = header; check it matches the expected CSV shape.
    if (!std::getline(file, line))
        throw std::runtime_error("Error: empty database file.");

    std::string hLeft, hRight;
    if (!splitOnChar(line, ',', hLeft, hRight)
        || trim(hLeft) != "date" || trim(hRight) != "exchange_rate")
        throw std::runtime_error("Error: malformed database header.");

    // Load the actual data lines.
    while (std::getline(file, line))
    {
        std::string date, rateStr;
        if (!splitOnChar(line, ',', date, rateStr))
            continue;

        date = trim(date);
        rateStr = trim(rateStr);

        double rate;
        if (!parseDouble(rateStr, rate) || rate < 0)
            continue;
        if (!isValidDate(date))
            continue;

        // insert: later duplicates keep the first value encountered.
        _rates.insert(std::make_pair(date, rate));
    }

    if (_rates.empty())
        throw std::runtime_error("Error: empty or invalid database.");
}

/*
** ---------------------------------------------------------------------------
** processFile
** ---------------------------------------------------------------------------
** Processes the input file ("date | value" per line) and prints, for each
** valid line, "date => value = result". Invalid lines print an error but are
** skipped, and the program always keeps going until the file is exhausted
** (a correction-sheet requirement).
** ---------------------------------------------------------------------------
*/
void BitcoinExchange::processFile(const std::string& inputFile) const
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line))
    {
        // trim() also removes '\r', so both LF and CRLF files work.
        std::string trimmed = trim(line);

        // Silent skip of blank/whitespace-only lines.
        if (trimmed.empty())
            continue;

        // The first real line must be the header and is skipped silently.
        if (firstLine)
        {
            firstLine = false;
            if (trimmed != "date | value")
            {
                std::cout << "Error: bad input => " << trimmed << std::endl;
                continue;
            }
            continue;
        }

        // Split around '|', then trim both sides so spacing is irrelevant.
        std::string date, valueStr;
        if (!splitOnChar(trimmed, '|', date, valueStr))
        {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }
        date = trim(date);
        valueStr = trim(valueStr);

        // The date must be a real YYYY-MM-DD calendar date.
        if (!isValidDate(date))
        {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }

        // The value must parse cleanly as a finite double.
        double value;
        if (!parseDouble(valueStr, value))
        {
            std::cout << "Error: bad input => " << trimmed << std::endl;
            continue;
        }

        // Value range checks. '-0' still checks value<0 false, so reject any
        // value whose text starts with a minus (a negative -> not positive).
        if (value < 0 || valueStr[0] == '-')
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        // Resolve the rate (exact date, else nearest lower). getRate fails
        // if the date is older than every entry in the database.
        double rate;
        if (!getRate(date, rate))
        {
            std::cout << "Error: no rate available before " << date
                      << "." << std::endl;
            continue;
        }

        std::cout << date << " => " << valueStr << " = "
                  << (value * rate) << std::endl;
    }
}

/*
** ---------------------------------------------------------------------------
** trim / splitOnChar
** ---------------------------------------------------------------------------
** trim strips leading and trailing spaces/tabs/carriage-returns. This is
** what makes CRLF files and flexible white-space work.
**
** splitOnChar finds the first 'sep' and splits the line into left/right.
** It returns false when no separator is present.
** ---------------------------------------------------------------------------
*/
std::string BitcoinExchange::trim(const std::string& s)
{
    std::string::size_type start = s.find_first_not_of(" \t\r");
    if (start == std::string::npos)
        return "";
    std::string::size_type end = s.find_last_not_of(" \t\r");
    return s.substr(start, end - start + 1);
}

bool BitcoinExchange::splitOnChar(const std::string& line, char sep,
                                  std::string& left, std::string& right)
{
    std::string::size_type pos = line.find(sep);
    if (pos == std::string::npos)
        return false;
    left = line.substr(0, pos);
    right = line.substr(pos + 1);
    return true;
}

/*
** ---------------------------------------------------------------------------
** parseDouble
** ---------------------------------------------------------------------------
** Robust numeric parser: rejects empty strings, non-parsable input, trailing
** junk ("1abc") and out-of-range / non-finite results (inf / nan),
** which strtod alone would silently accept.
** ---------------------------------------------------------------------------
*/
bool BitcoinExchange::parseDouble(const std::string& s, double& out)
{
    if (s.empty())
        return false;

    const char* cstr = s.c_str();
    char* end = NULL;
    errno = 0;
    double value = std::strtod(cstr, &end);

    if (end == cstr)            // nothing was parsed
        return false;
    if (*end != '\0')           // trailing junk remains
        return false;
    if (errno == ERANGE)        // overflow / underflow
        return false;
    if (!std::isfinite(value))  // inf / -inf / nan
        return false;

    out = value;
    return true;
}

/*
** ---------------------------------------------------------------------------
** isValidDate / isLeapYear
** ---------------------------------------------------------------------------
** isValidDate verifies a strict "YYYY-MM-DD" string and checks it encodes a
** real calendar date: month 1..12 and day within the correct number of days
** for that month/year (leap years give February 29 days).
** ---------------------------------------------------------------------------
*/
bool BitcoinExchange::isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.size() != 10)
        return false;

    static const int days[12] = {31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};

    // digits and '-' must sit at the right positions.
    for (std::string::size_type i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return false;
        }
        else if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;

    int maxDay = days[month - 1];
    if (month == 2 && isLeapYear(year))
        maxDay = 29;

    return day >= 1 && day <= maxDay;
}

/*
** ---------------------------------------------------------------------------
** getRate
** ---------------------------------------------------------------------------
** Returns the rate for the exact date if present; otherwise the rate of the
** closest date that is strictly LOWER than the requested date (never a
** higher one, per the subject). Returns false when no date at or before the
** requested one exists in the database.
**
** std::map keys are sorted, so lower_bound(date) yields the first entry
** whose key >= date. Stepping back one position gives the nearest lower
** date.
** ---------------------------------------------------------------------------
*/
bool BitcoinExchange::getRate(const std::string& date, double& rate) const
{
    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

    // Exact match -> use directly.
    if (it != _rates.end() && it->first == date)
    {
        rate = it->second;
        return true;
    }

    // Nothing at or before this date in the DB -> report failure.
    if (it == _rates.begin())
        return false;

    // Step back to the nearest date that is lower.
    --it;
    rate = it->second;
    return true;
}