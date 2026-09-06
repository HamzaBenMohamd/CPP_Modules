#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <stdexcept>
# include <climits>

class RPN 
{
    private:
        std::stack<int> _stack;

        bool isOperator(char c) const;
        void performOperation(char op);

    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        void calculate(const std::string &expression);
};

#endif
