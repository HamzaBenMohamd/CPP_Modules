
#include "RPN.hpp"

long operate(std::stack<long>& my_stack, char op)
{
    if (my_stack.size() < 2)
        throw std::logic_error("syntax err");
    long a = my_stack.top(); my_stack.pop();
    long b = my_stack.top(); my_stack.pop();

    if (op == '+')
        return b+a;
    else if (op == '-')
        return b-a;
    else if (op == '*')
        return b*a;
    else if (op == '/')
    {
        if (a == 0)
            throw std::logic_error("division by zero !");
        return b/a;
    }
    throw std::logic_error("invalid syntax");
}

bool    is_operator(char tkn)
{
    return (tkn == '+' || tkn == '-' || tkn == '*' || tkn == '/');
}

long RPN(str arg)
{
    std::stack<long> my_stack;
    long result = 0;
    std::stringstream ss(arg);
    char token;

    while (ss >> token)
    {
        if (std::isdigit(token))
            my_stack.push(token - '0');
        else if (is_operator(token))
            my_stack.push(operate(my_stack, token));
        else
            throw std::logic_error("syntax err: invalid token --> " + str(1, token));
    }
    if (my_stack.size() == 0)
        throw std::logic_error("syntax err");
    result = my_stack.top();
    my_stack.pop();
    if (my_stack.size() != 0)
        throw std::logic_error("syntax err");
    return result;
}
