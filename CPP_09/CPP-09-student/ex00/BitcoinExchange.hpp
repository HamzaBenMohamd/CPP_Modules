
#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

// date masks 
#define YY_MASK (0b11111111111111110000000000000000)
#define MM_MASK (0b00000000000000001111111100000000)
#define DD_MASK (0b00000000000000000000000011111111)

typedef std::string str;
typedef std::map<int, double> myMap;
typedef typename myMap::iterator iterator;

void    processData(std::ifstream& s, myMap& table, char delim, myMap& db);
void    execute(myMap& db, int date, double value);

#endif
