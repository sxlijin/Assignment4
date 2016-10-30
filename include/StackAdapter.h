#ifndef _STACK_ADAPTER_H_
#define _STACK_ADAPTER_H_

#include "StackBase.h"
#include <cstdlib>          // For size_t

/**
 * Transforms a specific container type into an implementation of the StackBase
 * interface. This class makes it possible to transform any container class with
 * a specific interface into a stack with the interface of the StackBase
 * abstract class. This adapter assumes that the parametrizing type has the
 * following properties:
 *   - a public value_type trait corresponding to the type of its elements.
 *   - an add(value_type) method
 *   - a const value_type& get(size_t) const method
 *   - a value_type& get(size_t) method
 *   - a remove(size_t) method
 *   - a size_t size() const method
 *
 * @author Krzysztof Zienkiewicz
 * @date October 21, 2011
 */
template <typename Container>
class StackAdapter : public StackBase<typename Container::value_type> {
public:

    typedef typename Container::value_type value_type;

    /**
     * Removes the top element from the stack. Throws Underflow if this stack
     * is empty.
     */
    virtual void pop();

    /**
     * Adds value to the top of the stack.
     *
     * @param
     */
    virtual void push(const value_type& value);

    /**
     * Returns the size of this stack.
     *
     * @return
     */
    virtual size_t size() const;

    /**
     * Returns a reference to the top of the stack. Throws Underflow if this
     * stack is empty.
     *
     * @return
     */
    virtual const value_type& top() const;

private:

    Container mContainer;
};

#include "../src/StackAdapter.cpp"

#endif
