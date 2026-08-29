#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include "NotFoundException.hpp"

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw NotFoundException();
    return it;
}

template <typename T>
typename T::const_iterator easyfind(const T &container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw NotFoundException();
    return it;
}

#endif
