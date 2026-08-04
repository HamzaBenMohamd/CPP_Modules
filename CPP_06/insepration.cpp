#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>

static bool isChar(const std::string& s) {
	if (s.size() == 1 && !isdigit(static_cast<unsigned char>(s[0])))
		return true;
	if (s.size() == 3 && s[0] == '\'' && s[2] == '\'')
		return true;
	return false;
}

static bool isPseudo(const std::string& s) {
	return s == "nan" || s == "nanf" || s == "inf" ||
		s == "+inf" || s == "-inf" || s == "inff" || 
		s == "+inff" || s == "-inff";
}

static void printChar(double d) {
	std::cout << "char: ";
	if (d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max())
		std::cout << "impossible";
	else {
		char c = static_cast<char>(d);
		if (!std::isprint(static_cast<unsigned char>(c)))
			std::cout << "Non displayable";
		else
			std::cout << "'" << c << "'";
	}
	std::cout << std::endl;
}

static void printInt(double d) {
	std::cout << "int: ";
	if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(d);
	std::cout << std::endl;
}

static std::string format_check(double v) {
	std::ostringstream os;
	os << v;
	std::string s = os.str();
	if (s.find('.') == std::string::npos && s.find('e') == std::string::npos
			&& s.find("inf") == std::string::npos && s.find("nan") == std::string::npos)
		s += ".0";
	return s;
}

static void printFloat(double d) {
	float f = static_cast<float>(d);
	std::cout << "float: " << format_check(static_cast<double>(f)) << "f" << std::endl;
}

static void printDouble(double d) {
	std::cout << "double: " << format_check(d) << std::endl;
}

static void fromPseudo(const std::string& s) {
	std::string fstr, dstr;
	if (s == "nan" || s == "nanf") {
		fstr = "nanf";
		dstr = "nan";
	} else {
		std::string sign = "";
		if (s[0] == '+' || s[0] == '-')
			sign = std::string(1, s[0]);
		fstr = sign + "inff";
		dstr = sign + "inf";
	}
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << fstr << std::endl;
	std::cout << "double: " << dstr << std::endl;
}

static void printImpossible() {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string& l) {
	if (isChar(l)) {
		char c = (l.size() == 1) ? l[0] : l[1];
		double d = static_cast<double>(c);
		printChar(d);
		printInt(d);
		printFloat(d);
		printDouble(d);
		return ;
	}
	if (isPseudo(l)) {
		fromPseudo(l);
		return;
	}
	std::string s = l;
	if (!s.empty() && (s[s.size() - 1] == 'f' || s[s.size() - 1] == 'F'))
		s = s.substr(0, s.size() - 1);
	std::stringstream ss(s);
	double d;
	ss >> d;
	if (ss.fail() || !ss.eof()) {
		printImpossible();
		return;
	}
	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}

