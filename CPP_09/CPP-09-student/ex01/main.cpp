
#include "RPN.hpp"

int main ( int ac, char **av )
{
    long result;

    if (ac != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    try {
        result = RPN(av[1]);
        std::cout << result << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    return 0;
}


