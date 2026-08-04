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

//? 
void ScalarConverter::convert(const std::string &literal)
{
    e_literal_type type = ScalarConverter::detectType(literal);
	std::cout << "Type: " << type << '\n';                                                         //! for debuging

    if (type == INVALID)
    {
        std::cout << "Error: invalid literal \"" << literal << "\"" << std::endl;
        return;
    }

    // =========================================================================
    // STEP B - STORAGE + "IMPOSSIBLE" FLAGS
    //   c_val / i_val / f_val / d_val : the final values that will be printed.
    //   imp_c / imp_i / imp_f / imp_d : true when that conversion "does not make
    //   sense or overflows" (subject wording) -> we print "impossible".
    // =========================================================================
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
			//logic: convert string to long using strtol() and check it's errno because it set an errno,
			//		if the number is larger than long_max or long_min,
			//		and check using if else if the number is > int_max or < int_min

            char *endptr;                           // will point past the parsed number
            long actual_long = std::strtol(literal.c_str(), &endptr, 10); //todo understand this strtol fun and it's parameters

            // overflow check vs the int range
            if (actual_long > std::numeric_limits<int>::max() || actual_long < std::numeric_limits<int>::min())
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

                // value fits an int but not a char
                if (actual_int < std::numeric_limits<char>::min() || actual_int > std::numeric_limits<char>::max())
                    imp_c = true;
            }
            break;
        }

        // ---------------------------------------------------------------------
        // CASE FLOAT : literal is a float like "42.0f", "-4.2f", or the
        //   pseudo-literals "nanf", "+inff", "-inff".
        //   C++98 has no std::strtof -> use std::strtod then cast to float.
        //   For the float pseudo-literals, char and int are impossible
        //   (NaN/inf are not representable in those types), but float and
        //   double ARE representable -> we keep imp_f / imp_d false.
        //   For normal floats: check the int/char ranges, like in the INT case.
        // ---------------------------------------------------------------------
        case FLOAT:
        {
            char *endptr;
            float actual_float = static_cast<float>(std::strtod(literal.c_str(), &endptr));

            f_val = actual_float;                       // actual type

            c_val = static_cast<char>(actual_float);
            i_val = static_cast<int>(actual_float);
            d_val = static_cast<double>(actual_float);

            if (literal == "nanf" || literal == "-inff" || literal == "+inff")
            {
                imp_c = imp_i = true;                   // NaN/inf -> no char, no int
            }
            else
            {
                if (actual_float > static_cast<float>(std::numeric_limits<int>::max())
                    || actual_float < static_cast<float>(std::numeric_limits<int>::min()))
                    imp_i = true;
                if (actual_float > static_cast<float>(std::numeric_limits<char>::max())
                    || actual_float < static_cast<float>(std::numeric_limits<char>::min()))
                    imp_c = true;
            }
            break;
        }

        // ---------------------------------------------------------------------
        // CASE DOUBLE : literal is a double like "4.2" or the pseudo-literals
        //   "nan", "+inf", "-inf". Same logic as FLOAT, but the actual type is
        //   double (no extra strtod->float cast).
        // ---------------------------------------------------------------------
        case DOUBLE:
        {
            char *endptr;
            double actual_double = std::strtod(literal.c_str(), &endptr);

            d_val = actual_double;                      // actual type

            c_val = static_cast<char>(actual_double);
            i_val = static_cast<int>(actual_double);
            f_val = static_cast<float>(actual_double);

            if (literal == "nan" || literal == "-inf" || literal == "+inf")
            {
                imp_c = imp_i = true;                   // NaN/inf -> no char, no int
            }
            else
            {
                if (actual_double > static_cast<double>(std::numeric_limits<int>::max())
                    || actual_double < static_cast<double>(std::numeric_limits<int>::min()))
                    imp_i = true;
                if (actual_double > static_cast<double>(std::numeric_limits<char>::max())
                    || actual_double < static_cast<double>(std::numeric_limits<char>::min()))
                    imp_c = true;
            }
            break;
        }
        default:
            break;
    }

    // =========================================================================
    // STEP D - PRINT THE 4 LINES (exact order required by the subject)
    //   format:  char:  X
    //            int:   X
    //            float: Xf
    //            double:X
    // =========================================================================

    // --- CHAR : 3 possible outputs ---
    //   "impossible"      -> NaN/inf OR out of char range (imp_c)
    //   "Non displayable" -> printable? no (use std::isprint)
    //   "'<c>'"           -> printable character
    std::cout << "char: ";
    if (imp_c)
        std::cout << "impossible";
    else if (!std::isprint(static_cast<unsigned char>(c_val)))
        std::cout << "Non displayable";
    else
        std::cout << "'" << c_val << "'";
    std::cout << "\n";

    // --- INT : impossible or the number itself ---
    std::cout << "int: ";
    if (imp_i)
        std::cout << "impossible";
    else
        std::cout << i_val;
    std::cout << "\n";

    // --- FLOAT : value + mandatory trailing 'f' ---
    //   The subject prints "0.0f" and "42.0f", so a whole number must show a
    //   trailing ".0". We append ".0" when the value has no fractional part
    //   (f_val == floor(f_val)) AND is not a pseudo-literal (!imp_i).
    //   Note: for a pseudo-literal, cout prints "nan"/"inf" and imp_i is true,
    //   so no ".0" is appended -> "nanf"/"inff" as expected.
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

    // --- DOUBLE : value, same whole-number ".0" rule, no 'f' suffix ---
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
