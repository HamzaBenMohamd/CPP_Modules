
#include "BitcoinExchange.hpp"

/*
 * date is defined as int type for izi comparision
 * if date is YYYY-MM-DD
 *              |   |  |
 *         (2 bytes)|  +------+
 *                  |         +---+
 *                  |->(1byte)    |
 *                                +-----> (1byte)
 *
 * THEN the int representation of it is:
 * 	intRep = YYYY << (256**2) + MM << 256 + DD
 *
 * this makes the comparision izi without needing to do operator
 * overloading. See :
 *
 * normal integer comparision gives priority to MSBs then LSBs
 * in our examples its means giving priority to YEAR bits
 * then MONTH bits then finally DAY bits.
 *
 *
 * now int to date ?
 * izi : (we use bit masking)
 *
 * DD = intRep & (00000000_00000000_00000000_11111111)
 * MM = intRep & (00000000_00000000_11111111_00000000)
 * YY = intRep & (11111111_11111111_00000000_00000000)
 *
 */

static int  date2Int(long YY, long MM, long DD)
{
    int date = 0;
    date |= YY << 16;
    date |= MM << 8;
    date |= DD;
    return date;
}

static str  int2Date(int date)
{
    int YY = (date & YY_MASK) >> 16;
    int MM = (date & MM_MASK) >> 8;
    int DD = (date & DD_MASK);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << YY << "-";
    ss << std::setw(2) << std::setfill('0') << MM << "-";
    ss << std::setw(2) << std::setfill('0') << DD;

    return ss.str();
}

void    parseObj(str line, int& date, double& value, char delim)
{
    long YY, MM, DD;
    char dash0, dash1, dash2;
    str rest;

    std::stringstream ss(line);

    ss >> YY >> dash0
       >> MM >> dash1
       >> DD >> dash2;

    if (!(ss >> value) || (ss >> rest))
        throw std::logic_error("bad input => " + line);

    if (dash0 != '-' || dash1 != '-' || dash2 != delim || rest != "")
        throw std::logic_error("bad input => " + line);

    date = date2Int(YY, MM, DD);

    if (
        YY < 0 || YY > 9999 ||
        MM < 0 || MM > 12 ||
        DD < 0 || DD > 31
    )
    {
        std::stringstream err;
        err << YY << "-" << MM << "-" << DD;
        throw std::logic_error("bad input => " + line);
    }


    if (value < 0)
        throw std::logic_error("not a positive number.");
    if (value > 1000 && delim == '|')
        throw std::logic_error("too large a number.");
}

void    processData(std::ifstream& s, myMap& table, char delim, myMap& db)
{
    str header;
    str line;
    int         date = 0;
    double      value = 0;

    if (!s.is_open())
        throw std::logic_error("could not open file.");

    // verify header
    getline(s, header);
    if (
        !(header == "date | value" && delim == '|')
        && !(header == "date,exchange_rate" && delim == ',')
    )
        throw std::logic_error("Wrong Header.");

    while (getline(s, line))
    {
        try {
            std::stringstream ss(line);
            str test;
            ss >> test;
            if (test.empty())
                continue ;

            parseObj(line, date, value, delim);
            table[date] = value;
            if (delim == '|')
                execute(db, date, value);
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

static double   findDateInDB(int date, myMap& db)
{
    double  lower_bound = db.begin()->second;

    for (
        iterator it = db.begin();
        it != db.end();
        ++it
    )
    {
        if (date == it->first)
            return it->second;
        else if (it->first < date)
            lower_bound = it->second;
        else
            break;
    }
    return lower_bound;
}

void    execute(myMap& db, int date, double value)
{
    double   exchange_rate;

    if (db.empty())
        throw std::logic_error("Empty DataBase !");

    exchange_rate = findDateInDB(date, db);
    // display
    std::cout << int2Date(date) << " => "
                << value << " = "
                << value * exchange_rate
                << std::endl;
}
