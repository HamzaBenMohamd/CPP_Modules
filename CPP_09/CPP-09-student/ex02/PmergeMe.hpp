
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <sstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <sys/time.h>

typedef std::string str;
typedef std::vector<long> vec;
typedef std::deque<long> deque;

// parsing
void        parseContainer(int ac, char **av, vec& list);
void        parseContainer(int ac, char **av, deque& list);

// Algo for vec
void    getMainChain(vec& list, vec& mainChain, vec& pend);
void    insertElm(vec& pend, vec& mainChain, unsigned long Ji);
void    insert(vec& pend, vec& mainChain);
void    Ford_Jhonson(vec& list, double& duration);
void    _Ford_Jhonson(vec& list);

// Algo for deque
void    getMainChain(deque& list, deque& mainChain, deque& pend);
void    insertElm(deque& pend, deque& mainChain, unsigned long Ji);
void    insert(deque& pend, deque& mainChain);
void    Ford_Jhonson(deque& list, double& duration);
void    _Ford_Jhonson(deque& list);

#endif
