#include "RPN.hpp"

//? 
RPN::RPN() {}

//? 
RPN::RPN(const RPN &other) : _stack(other._stack) {}

//?
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other) 
        _stack = other._stack;
    return *this;
}

//?
RPN::~RPN() {}

//? 
void RPN::calculate(const std::string &expression)
{
    for (size_t i = 0; i < expression.length(); ++i) // i = 5
    {
        char c = expression[i];

        // 1. Skip spaces safely
        if (c == ' ')
            continue;

        // 2. Identify single digit numbers and push them
        if (std::isdigit(c))
        {
            // Convert the ASCII character to its actual integer value
            _stack.push(c - '0');
        }
        // 3. Identify operators and trigger calculation
        else if (isOperator(c))
        {
            performOperation(c);
        }
        // 4. Reject any foreign characters (letters, decimals, brackets)
        else
        {
            throw std::runtime_error("Error");
        }
    }

    // After evaluating the entire string, exactly one number must remain
    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    // Print the final result
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
    // 1. Validate stack size
    if (_stack.size() < 2)
        throw std::runtime_error("Error");

    // 2. Extract operands (Order matters heavily here)
    int rhs = _stack.top(); // Right-hand side
    _stack.pop();
    
    int lhs = _stack.top(); // Left-hand side
    _stack.pop();

    long result = 0;

    // 3. Execute the specific math operation
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
            // Protect against division by zero
            if (rhs == 0)
                throw std::runtime_error("Error");
            result = static_cast<long>(lhs) / rhs;
            break;
    }

    // 4. Push the calculated result back to be used by the next operator
    _stack.push(static_cast<int>(result));
}
