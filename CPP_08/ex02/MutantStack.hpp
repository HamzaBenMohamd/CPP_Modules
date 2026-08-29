#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

// MutantStack is std::stack that became iterable.
// std::stack is only a container adapter: it hides the underlying container
// behind its public interface, so there is no way to iterate over it.
// The underlying container is stored in a *protected* member named "c", so a
// derived class may access it directly. Therefore we simply inherit from
// std::stack<T> and re-expose the iterators of that protected container.
template <typename T>
class MutantStack : public std::stack<T>
{
    public:
        MutantStack() : std::stack<T>()
        {
        }

        MutantStack(const MutantStack &other) : std::stack<T>(other)
        {
        }

        MutantStack &operator=(const MutantStack &other)
        {
            if (this != &other)
                std::stack<T>::operator=(other);
            return *this;
        }

        ~MutantStack()
        {
        }

        // All the iterator categories of the underlying container
        // (std::deque by default). We need "typename" because these are
        // nested types of a template-dependent base class.
        typedef typename std::stack<T>::container_type::iterator iterator;
        typedef typename std::stack<T>::container_type::const_iterator const_iterator;
        typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
        typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

        // Iteration in storage order: begin() -> first pushed, end() -> past the top.
        iterator begin() { return this->c.begin(); }
        iterator end() { return this->c.end(); }

        const_iterator begin() const { return this->c.begin(); }
        const_iterator end() const { return this->c.end(); }

        // Reverse order: begin from the top (last pushed) down to the bottom.
        reverse_iterator rbegin() { return this->c.rbegin(); }
        reverse_iterator rend() { return this->c.rend(); }

        const_reverse_iterator rbegin() const { return this->c.rbegin(); }
        const_reverse_iterator rend() const { return this->c.rend(); }
};

#endif