#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <stdexcept>
# include <cstdlib>
# include <sys/time.h>
# include <climits>
# include <algorithm>
# include <utility>

class PmergeMe
{
    private:
        std::vector<int>	_vector;
        std::deque<int>		_deque;

        void parseInput(int argc, char **argv);
		long calculateTimeDiff(const struct timeval& start, const struct timeval& end) const;
		void mergeInsertSortVector(std::vector<int> &arr);

        void sortVector();
        void sortDeque();

        template <typename Container>
        void printContainer(const std::string& prefix, const Container& c) const;

    public:
        //* OCF
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void process(int argc, char **argv);
};

//* print container
template <typename Container>
void PmergeMe::printContainer(const std::string &prefix, const Container &c) const
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
