#include "RPN.hpp"

//? Default Constructor
RPN::RPN() {}

//? Copy Constructor
RPN::RPN(const RPN &other) : _stack(other._stack) {}

//? Assignment Operator
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other) 
        _stack = other._stack;
    return *this;
}

//? Destructor
RPN::~RPN() {}

//? calculate the operation (ex: 8 4 /)
void RPN::calculate(const std::string &expression)
{
    for (size_t i = 0; i < expression.length(); ++i)
    {
        char c = expression[i];
        if (std::isspace(static_cast<unsigned char>(c)))
            continue;

        if (std::isdigit(static_cast<unsigned char>(c)))
            _stack.push(c - '0');
        else if (isOperator(c))
            performOperation(c);
        else
            throw std::runtime_error("Error");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << '\n';
}

//? check if c is a valid operator (+ - * /)
bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//? perform one operation (+ - * /)
void RPN::performOperation(char op)
{
    if (_stack.size() < 2)
        throw std::runtime_error("Error");

    int rhs = _stack.top();
    _stack.pop();
    int lhs = _stack.top();
    _stack.pop();
    long result = 0;
    switch (op)
    {
        case '+':
            result = static_cast<long>(lhs) + rhs;
            break;
        case '-':
            result = static_cast<long>(lhs) - rhs;
            break;
        case '*':
            result = static_cast<long>(lhs) * rhs;
            break;
        case '/':
            if (rhs == 0)
                throw std::runtime_error("Error");
            result = static_cast<long>(lhs) / rhs;
            break;
    }
	if (result > INT_MAX || result < INT_MIN)
	        throw std::runtime_error("Error");

    _stack.push(static_cast<int>(result));
}
