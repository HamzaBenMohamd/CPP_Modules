#include "PmergeMe.hpp"

//* --- Orthodox Canonical Form ---
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other)
    {
        this->_vector = other._vector;
        this->_deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

//* --- Input Parsing ---
void PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        
        if (arg.empty())
            throw std::runtime_error("empty argument.");

        // 1. Strictly enforce positive integers only
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::runtime_error("invalid character (only positive integers allowed).");
        }

        // 2. Convert and protect against integer overflow
        long val = std::strtol(arg.c_str(), NULL, 10);
        if (val > INT_MAX)
            throw std::runtime_error("number exceeds INT_MAX.");

        int num = static_cast<int>(val);

        // 3. Load the exact same data into both containers
        _vector.push_back(num);
        _deque.push_back(num);
    }
}

//* --- Time Helper ---
long PmergeMe::calculateTimeDiff(const struct timeval& start, const struct timeval& end) const
{
    return ((end.tv_sec - start.tv_sec) * 1000000L) + (end.tv_usec - start.tv_usec);
}

//* --- Main Orchestration (Updated) ---
void PmergeMe::process(int argc, char **argv)
{
    parseInput(argc, argv);

    printContainer("Before: ", _vector);

    struct timeval start, end;
    
    // --- Time the Vector ---
    gettimeofday(&start, NULL);
    sortVector(); 
    gettimeofday(&end, NULL);
    
    long timeVector = calculateTimeDiff(start, end); // Much cleaner!

    // --- Time the Deque ---
    gettimeofday(&start, NULL);
    sortDeque(); 
    gettimeofday(&end, NULL);
    
    long timeDeque = calculateTimeDiff(start, end);

    // --- Print Results ---
    printContainer("After:  ", _vector);

    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << timeVector << " us\n";
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque  : " << timeDeque << " us\n";
}

//todo: Stub sorting methods (To be implemented)
void PmergeMe::sortDeque() {}

void PmergeMe::sortVector()
{
    // Delegate the sorting to the recursive/helper function
    mergeInsertSortVector(_vector);
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &arr)
{
    // Base case: already sorted
    if (arr.size() < 2)
        return;

    // 1. Isolate the straggler if the total count is an odd number
    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;
    
    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    // 2. Group into pairs (Winner goes in 'first', Loser goes in 'second')
    std::vector< std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    // 3. Sort the pairs based on the Winner (the 'first' element). 
    // std::sort automatically sorts pairs by pair.first in C++98.
    std::sort(pairs.begin(), pairs.end());

    // 4. Split the sorted pairs into the Main Chain and the Pend
    std::vector<int> mainChain;
    std::vector<int> pend;

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        mainChain.push_back(pairs[i].first);  // The Winners
        pend.push_back(pairs[i].second);      // The Losers
    }

    // --- PHASE 1 COMPLETE ---
    
	//todo: compate from here (phase 2, phase 1 is understood)
    // (Phase 2: Jacobsthal Insertion will go here)

    // Temporary: just to prevent the function from destroying the data during testing
    arr = mainChain; 
}

