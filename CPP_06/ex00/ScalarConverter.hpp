#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <cerrno>
# include <climits>
# include <cctype>
# include <cmath>
# include <iomanip>
# include <limits>
# include <sstream>

class ScalarConverter
{
	private:
		enum e_literal_type
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};

		ScalarConverter();
		ScalarConverter(const ScalarConverter &copy);
		ScalarConverter &operator=(const ScalarConverter &assign);
		~ScalarConverter();

		//? static helpers:
        static e_literal_type detectType(const std::string &literal);

        static void printChar(char c_val, bool imp_c);
        static void printInt(int i_val, bool imp_i);
        static void printFloat(float f_val, bool imp_f, bool imp_i);
        static void printDouble(double d_val, bool imp_d, bool imp_i);

	public:
		static void convert(const std::string &literal);
};

#endif
