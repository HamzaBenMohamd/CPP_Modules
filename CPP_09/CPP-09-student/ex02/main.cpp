
#include "PmergeMe.hpp"

int main ( int ac, char **av )
{
    if (ac == 1)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    vec     vector;
    deque   deq;

    double duration1 = 0, duration2 = 0;

    try {
        //parsing 
        parseContainer(ac, av, vector);
        parseContainer(ac, av, deq);

        unsigned long len = vector.size();

        std::cout << "Before: ";
        for (unsigned long i = 0; i < vector.size(); i++)
            std::cout << vector[i] << " ";
        std::cout << std::endl;

        // sorting algo
        Ford_Jhonson(vector, duration1);
        Ford_Jhonson(deq, duration2);

        std::cout << "After: ";
        for (unsigned long i = 0; i < vector.size(); i++)
            std::cout << vector[i] << " ";
        std::cout << std::endl;

        std::cout << "Time to process a range of " << len << " elements with std::vector : " << duration1 << " us" << std::endl;
        std::cout << "Time to process a range of " << len << " elements with std::deque : " << duration2 << " us" << std::endl;

    } catch (std::exception& e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    

    
}


