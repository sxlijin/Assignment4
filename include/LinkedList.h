#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <cstdlib>          // For size_t
#include <memory>

// Forward declarations
template <typename T>
class LinkedListIterator;

template <typename T>
class LinkedListConstIterator;

template <typename T>
class LinkedListNode;

namespace std {
    class out_of_range;
}

/**
 * A node-backed list implementation. This class attempts to provide certain
 * levels of exception safety (consult each method documentation for specifics)
 * and as such several assumptions are made:
 * 1. The parametrizing type has a default constructor.
 * 2. The parametrizing type has a copy constructor.
 * 3. The parametrizing type has an assignment operator.
 * 4. The parametrizing type has a no-throw destructor.
 * 5. The parametrizing type has proper copy semantics.
 *
 * To eliminate complex edge cases, this LinkedList is implemented as a doubly-
 * linked, circular chain of nodes that always contains a "dummy" node. With
 * this approach we never have to worry about checking for head and tail or
 * empty conditions. The node class is designed in such a way as to reduce the
 * amount of code in the actual list implementation.
 * Implementation note 1: mTail should always point to the dummy node.
 * Implementation note 2: mTail->next should always point to the head node.
 *
 * Due to this node structure, most of the operations performed on the
 * LinkedList can execute safely without making backup copies of the list.
 *
 * This class provides a set of STL-style forward iterators. As with most
 * iterator implementations, modifying the LinkedList while iterating over it
 * invalidates all current iterators. Attempts to use invalidated iterators
 * constitutes undefined behavior.
 *
 * @author Krzysztof Zienkiewicz
 * @date October 11, 2011
 */
template <typename T>
class LinkedList {
public:

    // STL traits
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef LinkedListIterator<T> iterator;
    typedef LinkedListConstIterator<T> const_iterator;

    /**
     * Initializes an empty LinkedList.
     * This operation provides strong exception safety.
     */
    LinkedList();

    /**
     * Initializes the LinkedList to be a copy of src.
     * This operation provides strong exception safety.
     *
     * @param src LinkedList to copy
     */
    LinkedList(const LinkedList<T>& src);

    /**
     * Makes this object a copy of rhs using the same guidelines as the copy
     * constructor. Note that calling this method on yourself (l = l;) is
     * equivalent to a no-op.
     * This operation provides strong exception safety.
     *
     * @param rhs LinkedList to copy
     * @return *this, used for chaining.
     */
    const LinkedList<T>& operator=(const LinkedList<T>& rhs);

    /**
     * Destructor. Releases all resources held by this LinkedList.
     * This operation is no-throw under the assumption that the parametrizing
     * type's destructor is no-throw.
     */
    ~LinkedList() throw ();

    /**
     * Adds value to the end of this LinkedList. The insertion is performed in
     * constant time.
     * This operation provides strong exception safety.
     *
     * @param value value to append to this LinkedList
     */
    void add(const_reference value);

    /**
     * Inserts value at the specified index. All elements at or to the right of
     * index are shifted down by one spot. Time proportional to the maximum of
     * the size of this LinkedList or index is needed to perform this operation.
     * In particular, note that this operation does not perform the tail
     * insertion optimization that add(const_reference) offers. If this
     * LinkedList needs to be enlarged (index is out of range) default values
     * are used to fill the gaps.
     * This operation provides strong exception safety.
     *
     * @param index index at which to insert value
     * @param value the element to insert
     */
    void add(size_t index, const_reference value);

    /**
     * Empties this LinkedList returning it to the same state as the default
     * constructor.
     * This operation is no-throw under the assumption that the parametrizing
     * type's destructor is no-throw.
     */
    void clear() throw ();

    /**
     * Returns a constant reference to the element stored at the provided index.
     * If index is out of bounds, an std::out_of_range exception is thrown with
     * the index as its message.
     * This operation provides strong exception safety.
     *
     * @param index index of the element to return
     * @return constant reference to the element at the index.
     */
    const_reference get(size_t index) const throw (std::out_of_range);

    /**
     * Returns a reference to the element stored at the provided index. If index
     * is out of bounds, an std::out_of_range exception is thrown with the index
     * as its message.
     * This operation provides strong exception safety.
     *
     * @param index index of the element to return
     * @return reference to the element at the index.
     */
    reference get(size_t index) throw (std::out_of_range);

    /**
     * Returns true if this LinkedList is equal to rhs and false otherwise.
     * This operation provides strong exception safety.
     *
     * @param rhs
     * @return
     */
    bool operator==(const LinkedList<T>& rhs) const;

    /**
     * Returns false if this LinkedList is equal to rhs and true otherwise.
     * This operation provides strong exception safety.
     *
     * @param rhs
     * @return
     */
    bool operator!=(const LinkedList<T>& rhs) const;

    /**
     * Returns a constant iterator to the beginning.
     * This operation is a no-throw.
     *
     * @return
     */
    const_iterator begin() const throw ();

    /**
     * Returns an iterator to the beginning.
     * This operation is a no-throw.
     *
     * @return
     */
    iterator begin() throw ();

    /**
     * Returns a constant iterator to the end.
     * This operation is a no-throw.
     *
     * @return
     */
    const_iterator end() const throw ();

    /**
     * Returns an iterator to the end.
     * This operation is a no-throw.
     *
     * @return
     */
    iterator end() throw ();

    /**
     * Returns true if this LinkedList is empty and false otherwise.
     * This operation is a no-throw.
     *
     * @return
     */
    bool isEmpty() const throw ();

    /**
     * Removes the element at the specified index. If index is out of bounds
     * an std::out_of_range exception is thrown with index as its messaged. If
     * index points to the first or last element, this operation is performed in
     * constant time. Otherwise, time proportional to index is needed.
     * This operation is no-throw under the assumption that the parametrizing
     * type's destructor is no-throw.
     *
     * @param index index of the object to remove.
     */
    void remove(size_t index) throw (std::out_of_range);

    /**
     * Sets the element at the specified index to the provided value. If index
     * is out of bounds, an std::out_of_range exception is thrown with the index
     * as its message. This method completes in time proportional to index.
     * This operation provides strong exception safety.
     *
     * @param index index of the object to set
     * @param value the new value
     */
    void set(size_t index, const_reference value);


    /**
     * Return the size of this LinkedList.
     * This operation is a no-throw.
     *
     * @return
     */
    size_t size() const throw ();

private:

    /**
     * Given an index, this method throws an std::out_of_range with the index as
     * its message if index is out of bounds or is a no-op otherwise.
     * This operation provides strong exception safety.
     *
     * @param index index to check
     */
    void rangeCheck(size_t index) const throw (std::out_of_range);

    /**
     * Removes from this LinkedList the node pointed to by iter.
     * This operation is no-throw under the assumption that the parametrizing
     * type's destructor is no-throw.
     *
     * @param iter iterator pointing to the node that should be removed.
     */
    void removeNode(iterator iter) throw ();

    /**
     * Swaps the contents of this LinkedList with that of other in constant time.
     * This operation is a no-throw.
     *
     * @param other the LinkedList to swap with
     */
    void swap(LinkedList<T>& other) throw ();

    /**
     * The logical size of the list. This does not include the dummy node
     */
    size_t mSize;

    /**
     * (auto_) pointer to the dummy node. mTail->mNext point to the first valid
     * element of this list (if one exists). We use a smart pointer in order to
     * achieve strong exception safety in certain methods.
     */
    std::auto_ptr<LinkedListNode<T> > mTail;
};

/**
 * A helper utility class for implementing the LinkedList. Most of this class is
 * private so that only its friends may use its functionality.
 */
template <typename T>
class LinkedListNode {
public:

    /**
     * Initializes this node to store the provided item. The next and previous
     * pointers of this node are set to point to the node itself.
     * This operation provides strong exception safety.
     *
     * @param item the item to set
     */
    LinkedListNode(const T& item = T());

    /**
     * Destructor. Unlinks this node from its neighbors.
     * This operation is a no-throw.
     */
    ~LinkedListNode() throw ();

#ifdef GRADUATE_STUDENT
    void* operator new(size_t );

    void operator delete (void* ptr);

    static void addToPool(size_t n);

    static void clearPool(void);
#endif

private:

    static LinkedListNode<T>* sPool;

    friend class LinkedList<T>;
    friend class LinkedListIterator<T>;
    friend class LinkedListConstIterator<T>;

    /**
     * Initializes this node with the provided values. The nodes pointed to
     * by the pointer parameters have their state adjusted so that after
     * this operation completes, this node is inserted inbetween them.
     * This operation provides strong exception safety.
     *
     * @param item item to set
     * @param prev pointer to the previous node
     * @param next pointer to the next node
     */
    LinkedListNode(const T& item, LinkedListNode<T>* prev, LinkedListNode<T>* next);

    /**
     * Establishes the proper linkage between the provided nodes.
     *
     * @param
     * @param
     */
    static void link(LinkedListNode<T>* first, LinkedListNode<T>* second);

    T mItem;
    LinkedListNode<T>* mPrev;
    LinkedListNode<T>* mNext;
};

#include "../src/LinkedList.cpp"

#endif
