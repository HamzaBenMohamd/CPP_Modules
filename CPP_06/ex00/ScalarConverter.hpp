#ifndef ScalarConverter_HPP
# define ScalarConverter_HPP

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
		static e_literal_type    detectType(const std::string &literal);
		static void   printChar(double value); //? usless?
		static void   printInt(double value);
		static void   printFloat(double value);
		static void   printDouble(double value);

	public:
		static void convert(const std::string &literal);
};

#endif
