#include "ScalarConverter.hpp"

//? Default Constructor
ScalarConverter::ScalarConverter()
{
	std::cout << "Default Constructor called of ScalarConverter" << std::endl;
}

//? Copy Constructor
ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
	std::cout << "Copy Constructor called of ScalarConverter" << std::endl;
	*this = copy;
}

//? Destructor
ScalarConverter::~ScalarConverter()
{
	std::cout << "Destructor called of ScalarConverter" << std::endl;
}

//? Copy Assignment Operator
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &assign)
{
	std::cout << "Copy Assignment Operator called of ScalarConverter" << std::endl;
	if (this != &assign)
	{

	}
	return (*this);
}

//? Reads the string and decides which kind of literal it is
ScalarConverter::e_literal_type ScalarConverter::detectType(const std::string &literal)
{
	if (literal.empty())
		return INVALID;
	if (literal == "-inff" || literal == "+inff" || literal == "nanf")
		return FLOAT;
	if (literal == "-inf" || literal == "+inf" || literal == "nan")
		return DOUBLE;
	if (literal.size() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0]))) 
		return CHAR;

	bool hasDot = false;
	bool hasF = false;
	bool hasDigit = false;
	size_t i = 0;

	if (literal[0] == '+' || literal[0] == '-')
	{
		if (literal.size() == 1)
			return INVALID;
		i = 1;
	}

	for (; i < literal.size(); ++i)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])))
		{
			hasDigit = true;
			continue;
		}
		if (literal[i] == '.')
		{
			if (hasDot)
				return INVALID;
			hasDot = true;
			continue;
		}
		if (literal[i] == 'f' || literal[i] == 'F')
		{
			if (i != literal.size() - 1)
				return INVALID;
			hasF = true;
			continue;
		}
		return INVALID;
	}

	if (!hasDigit || (hasF && !hasDot))
		return INVALID;
	if (hasF)
		return FLOAT;
	if (hasDot)
		return DOUBLE;
	return INT;
}

//? convert literal to its type (if it's possible)
void ScalarConverter::convert(const std::string &literal) //todo test edge cases and make sure this fun is perfect! and meet the correction sheet and the subject's requirements (asigne this task to opencode)
{
    e_literal_type type = ScalarConverter::detectType(literal);

    if (type == INVALID)
    {
        std::cout << "Error: invalid literal \"" << literal << "\"" << std::endl;
        return;
    }

    char   c_val = 0;
    int    i_val = 0;
    float  f_val = 0.0f;
    double d_val = 0.0;

    bool imp_c = false;
    bool imp_i = false;
    bool imp_f = false;
    bool imp_d = false;

    switch (type)
    {
        case CHAR:
        {
            c_val = literal[0];
            i_val = static_cast<int>(literal[0]);
            f_val = static_cast<float>(literal[0]);
            d_val = static_cast<double>(literal[0]);
            break;
        }
        case INT:
        {
            errno = 0;
            char *endptr;
            long actual_long = std::strtol(literal.c_str(), &endptr, 10);

            if (errno == ERANGE || actual_long > std::numeric_limits<int>::max() || actual_long < std::numeric_limits<int>::min())
            {
                imp_c = imp_i = imp_f = imp_d = true;
            }
            else
            {
                int actual_int = static_cast<int>(actual_long);

                i_val = actual_int;
                c_val = static_cast<char>(actual_int);
                f_val = static_cast<float>(actual_int);
                d_val = static_cast<double>(actual_int);

                if (actual_int < std::numeric_limits<char>::min() || actual_int > std::numeric_limits<char>::max())
                    imp_c = true;
            }
            break;
        }
        case FLOAT:
        {
            char *endptr;
            errno = 0;
            
            double temp_double = std::strtod(literal.c_str(), &endptr);

            if (literal == "nanf" || literal == "-inff" || literal == "+inff")
            {
                f_val = static_cast<float>(temp_double);
                d_val = temp_double;
                imp_c = imp_i = true;
            }
            else
            {
                if (errno == ERANGE || temp_double > std::numeric_limits<float>::max() || temp_double < -std::numeric_limits<float>::max())
                {
                    imp_f = imp_c = imp_i = true;
                    d_val = temp_double;
                }
                else
                {
                    float actual_float = static_cast<float>(temp_double);
                    f_val = actual_float;
                    d_val = static_cast<double>(actual_float);

                    if (actual_float > static_cast<float>(std::numeric_limits<int>::max()) || actual_float < static_cast<float>(std::numeric_limits<int>::min()))
                        imp_i = true;
                    else
                        i_val = static_cast<int>(actual_float);

                    if (actual_float > static_cast<float>(std::numeric_limits<char>::max()) || actual_float < static_cast<float>(std::numeric_limits<char>::min()))
                        imp_c = true;
                    else
                        c_val = static_cast<char>(actual_float);
                }
            }
            break;
        }
        case DOUBLE: 
        {
            char *endptr;
            errno = 0;
            double actual_double = std::strtod(literal.c_str(), &endptr);

            if (literal == "nan" || literal == "-inf" || literal == "+inf")
            {
                d_val = actual_double;
                f_val = static_cast<float>(actual_double);
                imp_c = imp_i = true;
            }
            else
            {
                if (errno == ERANGE)
                    imp_d = imp_f = imp_c = imp_i = true;
                else
                {
                    d_val = actual_double;
                    if (actual_double > static_cast<double>(std::numeric_limits<float>::max()) || actual_double < -static_cast<double>(std::numeric_limits<float>::max()))
                        imp_f = true;
                    else
                        f_val = static_cast<float>(actual_double);
                    if (actual_double > static_cast<double>(std::numeric_limits<int>::max()) || actual_double < static_cast<double>(std::numeric_limits<int>::min()))
                        imp_i = true;
                    else
                        i_val = static_cast<int>(actual_double);
                    if (actual_double > static_cast<double>(std::numeric_limits<char>::max()) || actual_double < static_cast<double>(std::numeric_limits<char>::min()))
                        imp_c = true;
                    else
                        c_val = static_cast<char>(actual_double);
                }
            }
            break;
        }
        default:
            break;
    }

    //todo: use the helper function in the header file (printChar() ... ), to make the code more readable (opencode)
    std::cout << "char: ";
    if (imp_c)
        std::cout << "impossible";
    else if (!std::isprint(static_cast<unsigned char>(c_val)))
        std::cout << "Non displayable";
    else
        std::cout << "'" << c_val << "'";
    std::cout << "\n";

    std::cout << "int: ";
    if (imp_i)
        std::cout << "impossible";
    else
        std::cout << i_val;
    std::cout << "\n";

    std::cout << "float: ";
    if (imp_f)
        std::cout << "impossible";
    else
    {
        std::cout << f_val;
        if (f_val == std::floor(f_val) && !imp_i)
            std::cout << ".0";
        std::cout << "f";
    }
    std::cout << "\n";

    std::cout << "double: ";
    if (imp_d)
        std::cout << "impossible";
    else
    {
        std::cout << d_val;
        if (d_val == std::floor(d_val) && !imp_i)
            std::cout << ".0";
    }
    std::cout << "\n";
}
