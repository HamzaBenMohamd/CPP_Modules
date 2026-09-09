
#include "PmergeMe.hpp"




// Algo for vec
void    parseContainer(int ac, char **av, vec& list)
{
    long    parsed;
    str     rest;
    
    for (int i = 1; i < ac; i++)
    {
        std::stringstream ss(av[i]);

        if (!(ss >> parsed) || (ss >> rest))
            throw std::logic_error("Invalid Argument !");
        if (parsed < 0)
            throw std::logic_error("Negative Argument !");
        list.push_back(parsed);
    }
}

void getMainChain(vec& list, vec& mainChain, vec& pend)
{
    unsigned long len = list.size();

    for (unsigned long i = 0; i < (len-(len&1)); i+=2)
    {
        if (list[i] > list[i+1])
            std::swap(list[i], list[i+1]);
        mainChain.push_back(list[i+1]);
        pend.push_back(list[i]);
    }
}

void    insertElm(vec& pend, vec& mainChain, unsigned long Ji)
{
    if (Ji-1 >= pend.size())
        return ;
    long to_insert = pend[Ji-1];
    if (to_insert == -1)
        return ;
    mainChain.insert(
        std::lower_bound(mainChain.begin(), mainChain.end(), to_insert),
        to_insert
    );
    pend[Ji-1] = -1;
}

void insert(vec& pend, vec& mainChain)
{
    unsigned long k = pend.size();
    unsigned long J0 = 0;
    unsigned long J1 = 1;
    unsigned long Ji = J1 + 2*J0;

    for (unsigned long i = 0; i < k; i++)
    {
        // insert to main chain
        insertElm(pend, mainChain, Ji);
        J0 = J1;
        J1 = Ji;
        Ji = J1 + 2*J0;
    }
    for (unsigned long i = 0; i < k; i++)
        insertElm(pend, mainChain, i+1);
}

void        Ford_Jhonson(vec& list, double& duration)
{
    struct timeval tv;

    // benchmarking
    gettimeofday(&tv, NULL);
    double start = tv.tv_usec + tv.tv_sec * 1e6;

    // algo
    _Ford_Jhonson(list);

    // end
    gettimeofday(&tv, NULL);
    double end = tv.tv_usec + tv.tv_sec * 1e6;
    duration = end - start;
}

void        _Ford_Jhonson(vec& list)
{
    unsigned long   len = list.size();
    long            struggler = list[len-1];
    vec             mainChain, pend;

    if (len == 1)
        return ;
    getMainChain(list, mainChain, pend);
    _Ford_Jhonson(mainChain);
    // insert
    insert(pend, mainChain);
    if (len&1)
    {
        mainChain.insert(
            std::lower_bound(mainChain.begin(), mainChain.end(), struggler),
            struggler
        );
    }
    list = mainChain;
}













// Algo for deque
void    parseContainer(int ac, char **av, deque& list)
{
    long    parsed;
    str     rest;
    
    for (int i = 1; i < ac; i++)
    {
        std::stringstream ss(av[i]);

        if (!(ss >> parsed) || (ss >> rest))
            throw std::logic_error("Invalid Argument !");
        if (parsed < 0)
            throw std::logic_error("Negative Argument !");
        list.push_back(parsed);
    }
}

void getMainChain(deque& list, deque& mainChain, deque& pend)
{
    unsigned long len = list.size();

    for (unsigned long i = 0; i < (len-(len&1)); i+=2)
    {
        if (list[i] > list[i+1])
            std::swap(list[i], list[i+1]);
        mainChain.push_back(list[i+1]);
        pend.push_back(list[i]);
    }
}

void    insertElm(deque& pend, deque& mainChain, unsigned long Ji)
{
    if (Ji-1 >= pend.size())
        return ;
    long to_insert = pend[Ji-1];
    if (to_insert == -1)
        return ;
    mainChain.insert(
        std::lower_bound(mainChain.begin(), mainChain.end(), to_insert),
        to_insert
    );
    pend[Ji-1] = -1;
}

void insert(deque& pend, deque& mainChain)
{
    unsigned long k = pend.size();
    unsigned long J0 = 0;
    unsigned long J1 = 1;
    unsigned long Ji = J1 + 2*J0;

    for (unsigned long i = 0; i < k; i++)
    {
        // insert to main chain
        insertElm(pend, mainChain, Ji);
        J0 = J1;
        J1 = Ji;
        Ji = J1 + 2*J0;
    }
    for (unsigned long i = 0; i < k; i++)
        insertElm(pend, mainChain, i+1);
}

void        Ford_Jhonson(deque& list, double& duration)
{
    struct timeval tv;

    // benchmarking
    gettimeofday(&tv, NULL);
    double start = tv.tv_usec + tv.tv_sec * 1e6;

    // algo
    _Ford_Jhonson(list);

    // end
    gettimeofday(&tv, NULL);
    double end = tv.tv_usec + tv.tv_sec * 1e6;
    duration = end - start;
}

void        _Ford_Jhonson(deque& list)
{
    unsigned long   len = list.size();
    long            struggler = list[len-1];
    deque           mainChain, pend;

    if (len == 1)
        return ;
    getMainChain(list, mainChain, pend);
    _Ford_Jhonson(mainChain);
    // insert
    insert(pend, mainChain);
    if (len&1)
    {
        mainChain.insert(
            std::lower_bound(mainChain.begin(), mainChain.end(), struggler),
            struggler
        );
    }
    list = mainChain;
}


