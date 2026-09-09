#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <stdexcept>
# include <cstdlib>
# include <sys/time.h> // Required for microsecond timing
# include <climits>

# include <algorithm> // For std::sort and std::lower_bound
# include <utility>   // For std::pair

class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int>  _deque;

        // Core workflow helpers
        void parseInput(int argc, char** argv);
        
		long calculateTimeDiff(const struct timeval& start, const struct timeval& end) const;

		void mergeInsertSortVector(std::vector<int> &arr);
		
        // Ford-Johnson Algorithm implementations
        void sortVector();
        void sortDeque();

        // Template helper to print either container cleanly
        template <typename Container>
        void printContainer(const std::string& prefix, const Container& c) const;

    public:
        // Orthodox Canonical Form
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        // Main execution entry point
        void process(int argc, char** argv);
};

// C++98 requires template definitions to be in the header file
template <typename Container>
void PmergeMe::printContainer(const std::string& prefix, const Container& c) const
{
    std::cout << prefix;
    typename Container::const_iterator it;
    for (it = c.begin(); it != c.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';
}

#endif
