#include "PmergeMe.hpp"

//* --- Orthodox Canonical Form ---
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) 
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

        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::runtime_error("invalid character (only positive integers allowed).");
        }

        long val = std::strtol(arg.c_str(), NULL, 10);
        if (val > INT_MAX)
            throw std::runtime_error("number exceeds INT_MAX.");

        int num = static_cast<int>(val);
        _vector.push_back(num);
        _deque.push_back(num);
    }
}

//* --- Calculate Time ---
long PmergeMe::calculateTimeDiff(const struct timeval &start, const struct timeval &end) const
{
    return ((end.tv_sec - start.tv_sec) * 1000000L) + (end.tv_usec - start.tv_usec);
}

//* --- process fun ---
void PmergeMe::process(int argc, char **argv)
{
    parseInput(argc, argv);

    printContainer("Before: ", _vector);

    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    sortVector(); 
    gettimeofday(&end, NULL);
    
    long timeVector = calculateTimeDiff(start, end);

    // --- Time the Deque ---
    gettimeofday(&start, NULL);
    sortDeque(); 
    gettimeofday(&end, NULL);
    
    long timeDeque = calculateTimeDiff(start, end);

    printContainer("After:  ", _vector);

    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << timeVector << " us\n";
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque  : " << timeDeque << " us\n";
}

//* Sort Vector
void PmergeMe::sortVector()
{
    mergeInsertSortVector(_vector);
}

//* --- Ford-Johnson Algorithm (Merge-Insertion Sort) ---
// This algorithm sorts elements by minimizing the number of comparisons.
// It works in 3 main phases: Pairing, Recursive Sorting, and Binary Insertion.
void PmergeMe::mergeInsertSortVector(std::vector<int> &arr) //* 8 3 1 7 0 10 2 5
{
    // Base case: If 0 or 1 element, it's already sorted.
    if (arr.size() < 2)
        return;

    //* --- Phase 1: Preparation ---
    // If we have an odd number of elements, we take the last one out (the "straggler").
    // Example: [4, 2, 7, 1, 3] -> straggler is 3, we work with [4, 2, 7, 1]
    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    // Pair elements and swap them so the larger element is always second.
    // Example: [4, 2, 7, 1] -> Pairs: (2, 4), (1, 7)
    std::vector< std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] < arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    // Create a "Main Chain" consisting of the larger elements from each pair.
    // Example: From (2, 4) and (1, 7), mainChain is [4, 7]
    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        mainChain.push_back(pairs[i].second);
    }

    //* --- Phase 2: Recursion ---
    // Sort the Main Chain recursively using the same logic.
    // This ensures the "backbone" of our list is sorted.
    mergeInsertSortVector(mainChain); //* mainChain => 8, 10

    // Rebuild the "Pend" (pending elements) based on the sorted Main Chain.
    // We look at each element in the sorted mainChain and find its original smaller partner.
    // Example: If mainChain is [4, 7], and original pairs were (2, 4) and (1, 7),
    // pend will be [2, 1].
    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].second == mainChain[i])
            {
                pend.push_back(pairs[j].first);
                pairs[j].second = -1; // Mark as used
                break;
            }
        }
    }

    // If we had an odd element earlier, it joins the pend group now.
    if (hasStraggler)
    {
        pend.push_back(straggler);
    }

	// NEW: Save a snapshot of mainChain so we know exactly who the winners are
	std::vector<int> originalMainChain = mainChain;

    //* --- Phase 3: Binary Insertion ---
    // The first element of pend is special: it's paired with the smallest element of mainChain.
    // Therefore, it's guaranteed to be smaller than mainChain[0], so we insert it at the start.
    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0]);
    }

    // We use Jacobsthal numbers (1, 3, 5, 11...) to determine the order of insertion.
    // This specific order minimizes the maximum number of comparisons needed during binary search.
    std::vector<size_t> jacobSequence;
    size_t prev = 1;
    size_t curr = 3;
    jacobSequence.push_back(1);
    jacobSequence.push_back(3);
    while (curr < pend.size())
    {
        size_t next = curr + (2 * prev);
        jacobSequence.push_back(next);
        prev = curr;
        curr = next;
    }

    // Calculate the exact order to insert pend elements into mainChain.
    // We insert in "batches" backward from the next Jacobsthal number.
    std::vector<size_t> insertOrder;
    size_t lastJac = 1;
    for (size_t i = 1; i < jacobSequence.size(); ++i)
    {
        size_t j = jacobSequence[i];
        if (j > pend.size())
            j = pend.size(); 
            
        for (size_t k = j; k > lastJac; --k)
        {
            insertOrder.push_back(k - 1); 
        }
        lastJac = j;
    }

    // Finally, insert each element from pend into mainChain using Binary Search (std::lower_bound).
    for (size_t i = 0; i < insertOrder.size(); ++i)
    {
        size_t index = insertOrder[i];
	
       // Skip index 0 because we already manually inserted pend[0]
        if (index == 0) continue; 
	
    	int valueToInsert = pend[index];
        std::vector<int>::iterator bound;
	
       // 1. Is this the straggler?
        // The straggler (the last item in pend) never had a winner.
        // Therefore, its upper bound must be the end of the chain.
        if (hasStraggler && index == pend.size() - 1)
        {
            bound = mainChain.end();
        }
        else
        {
            // 2. Look up the winner's value in our snapshot
            int winnerValue = originalMainChain[index];
		
           // 3. Find exactly where that winner is sitting right now.
            // (Requires #include <algorithm> for std::find)
            bound = std::find(mainChain.begin(), mainChain.end(), winnerValue);
        }
		
       // 4. Binary search ONLY up to the winner's position! (Implementing your comment)
        std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), bound, valueToInsert); 
		
    	mainChain.insert(it, valueToInsert);
    }
    // The original array is now fully sorted.
    arr = mainChain;
}

void PmergeMe::sortDeque()
{
    mergeInsertSortDeque(_deque);
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &arr)
{
    if (arr.size() < 2)
        return;

    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    std::deque< std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] < arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        mainChain.push_back(pairs[i].second);
    }

    mergeInsertSortDeque(mainChain);

    std::deque<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].second == mainChain[i])
            {
                pend.push_back(pairs[j].first);
                pairs[j].second = -1;
                break;
            }
        }
    }

    if (hasStraggler)
    {
        pend.push_back(straggler);
    }

	std::deque<int> originalMainChain = mainChain;

    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0]);
    }
    std::deque<size_t> jacobSequence;
    size_t prev = 1;
    size_t curr = 3;
    jacobSequence.push_back(1);
    jacobSequence.push_back(3);
    while (curr < pend.size())
    {
        size_t next = curr + (2 * prev);
        jacobSequence.push_back(next);
        prev = curr;
        curr = next;
    }

    std::deque<size_t> insertOrder;
    size_t lastJac = 1;
    for (size_t i = 1; i < jacobSequence.size(); ++i)
    {
        size_t j = jacobSequence[i];
        if (j > pend.size())
            j = pend.size(); 
            
        for (size_t k = j; k > lastJac; --k)
        {
            insertOrder.push_back(k - 1); 
        }
        lastJac = j;
    }

    for (size_t i = 0; i < insertOrder.size(); ++i)
    {
        size_t index = insertOrder[i];
	
        if (index == 0) continue; 
	
    	int valueToInsert = pend[index];
        std::deque<int>::iterator bound;
        if (hasStraggler && index == pend.size() - 1)
        {
            bound = mainChain.end();
        }
        else
        {
            int winnerValue = originalMainChain[index];
		
            bound = std::find(mainChain.begin(), mainChain.end(), winnerValue);
        }
		
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), bound, valueToInsert); 
		
    	mainChain.insert(it, valueToInsert);
    }
    arr = mainChain;

}
