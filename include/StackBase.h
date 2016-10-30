#ifndef _STACK_BASE_H_
#define _STACK_BASE_H_

#include <cstdlib>      // For size_t

/**
 * An abstract base class for classes implementing the Stack ADT. This class
 * defines the classical interface for stacks.
 *
 * @author Krzysztof Zienkiewicz
 * @date October 21, 2011
 */
template <typename T>
class StackBase {
public:

    /**
     * Pure virtual destructor.
     */
    virtual ~StackBase() = 0;

    /**
     * Returns true if this stack is empty.
     *
     * @return
     */
    bool isEmpty() const;

    /**
     * Removes the top element from the stack. Throws Underflow if this stack
     * is empty.
     */
    virtual void pop() = 0;

    /**
     * Adds value to the top of the stack.
     *
     * @param
     */
    virtual void push(const T& value) = 0;

    /**
     * Returns the size of this stack.
     *
     * @return
     */
    virtual size_t size() const = 0;

    /**
     * Returns a reference to the top of the stack. Throws Underflow if this
     * stack is empty.
     *
     * @return
     */
    virtual const T& top() const = 0;

    /**
     * Returns a reference to the top of the stack. Throws Underflow if this
     * stack is empty.
     *
     * @return
     */
    T& top();

    /**
     * An exception class used when an empty stack is asked for the top element.
     */
    class Underflow {};
};

#include "../src/StackBase.cpp"

#endif
