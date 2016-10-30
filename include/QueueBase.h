#ifndef _QUEUE_BASE_H_
#define _QUEUE_BASE_H_

#include <cstdlib>      // For size_t

/**
 * An abstract base class for classes implementing the Queue ADT. This class
 * defines the classical interface for queues.
 *
 * @author Krzysztof Zienkiewicz
 * @date October 21, 2011
 */
template <typename T>
class QueueBase {
public:

    /**
     * Pure virtual destructor.
     */
    virtual ~QueueBase() = 0;

    /**
     * Removes the front element from this queue. Throws Underflow if this queue
     * is empty.
     */
    virtual void dequeue() = 0;

    /**
     * Adds value to the end of this queue.
     *
     * @param
     */
    virtual void enqueue(const T& value) = 0;

    /**
     * Returns a reference to the front of this queue. Throws Underflow if this
     * queue is empty.
     *
     * @return
     */
    virtual const T& front() const = 0;

    /**
     * Returns a reference to the front of this queue. Throws Underflow if this
     * queue is empty.
     *
     * @return
     */
    T& front();

    /**
     * Returns true if this queue is empty.
     *
     * @return
     */
    bool isEmpty() const;

    /**
     * Returns the size of this queue.
     *
     * @return
     */
    virtual size_t size() const = 0;

    /**
     * An exception class used when an empty queue is asked for the front
     * element.
     */
    class Underflow {};
};

#include "../src/QueueBase.cpp"

#endif

