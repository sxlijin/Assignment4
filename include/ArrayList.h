#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <cstdlib>          // For size_t
#include "ScopedArray.h"

// Forward declarations
template <typename T>
class ArrayListIterator;

template <typename T>
class ArrayListConstIterator;

namespace std {
    class out_of_range;
}

/**
 * An array-backed list implementation. This class attempts to provide certain
 * levels of exception safety (consult each method documentation for specifics)
 * and as such several assumptions are made:
 * 1. The parametrizing type has a default constructor.
 * 2. The parametrizing type has a copy constructor.
 * 3. The parametrizing type has an assignment operator.
 * 4. The parametrizing type has a no-throw destructor.
 * 5. The parametrizing type has proper copy semantics.
 *
 * An ArrayList object may internally hold more memory than size() implies. This
 * extra space (excess capacity) can be used to efficiently (and safely) add
 * elements to the end of the list. Unless otherwise stated, all methods that
 * need to allocate more space to execute will request twice the memory that is
 * actually needed (i.e., capacity will be twice the size after the operation
 * completes).
 *
 * This class provides a set of STL-style random access iterators. As with most
 * iterator implementations, modifying the ArrayList while iterating over it
 * invalidates all current iterators. Attempts to use invalidated iterators
 * constitutes undefined behavior.
 *
 * @author Krzysztof Zienkiewicz
 * @date September 30, 2011
 */
template <typename T>
class ArrayList {
public:

    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef ArrayListIterator<T> iterator;
    typedef ArrayListConstIterator<T> const_iterator;

    /**
     * Initializes the ArrayList with size elements all set to value. If size is
     * not supplied, an empty ArrayList is created. If value is not supplied,
     * the default value for the parametrized type will be used.
     * This operation provides strong exception safety.
     *
     * @param size size of the ArrayList to create
     * @param value value used to fill the ArrayList
     */
    explicit ArrayList(size_t size = 0, const_reference value = value_type());

    /**
     * Initializes the ArrayList to be a copy of src. Only the logical values of
     * src are copied. This means that any excess capacity of src is ignored.
     * This operation provides strong exception safety.
     *
     * @param src ArrayList to copy
     */
    ArrayList(const ArrayList<T>& src);

    /**
     * Makes this object a copy of rhs using the same guidelines as the copy
     * constructor. Note that calling this method on yourself (a = a;) is
     * equivalent to a no-op.
     * This operation provides strong exception safety.
     *
     * @param src ArrayList to copy
     * @return *this, used for chaining.
     */
    const ArrayList<T> &operator=(const ArrayList<T>& rhs);

    /**
     * Adds value to the end of this ArrayList. If we have excess capacity,
     * the insertion is performed in constant time. Otherwise, time proportional
     * to the size of this ArrayList is needed.
     * This operation provides strong exception safety.
     *
     * @param value value to append to this ArrayList
     */
    void add(const_reference value);

    /**
     * Inserts value at the specified index. All elements at or to the right of
     * index are shifted down by one spot. Time proportional to the size of this
     * ArrayList is needed to perform this operation. In particular, note that
     * this operation does not perform the tail insertion optimization that
     * add(const_reference) offers.
     * If this ArrayList needs to be enlarged, default values are used to fill
     * the gaps.
     * This operation provides strong exception safety.
     *
     * @param index index at which to insert value
     * @param value the element to insert
     */
    void add(size_t index, const_reference value);

    /**
     * Empties this ArrayList releasing all of its resources (i.e., returning
     * this ArrayList to the same state as the default constructor).
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
     * Returns a constant reference to the element stored at the provided index.
     * No range checking is performed on the index.
     * This operation is no-throw.
     *
     * @param index index of the element to return
     * @return constant reference to the element at the index.
     */
    const_reference operator[](size_t index) const throw ();

    /**
     * Returns a reference to the element stored at the provided index. No range
     * checking is performed on the index.
     * This operation is no-throw.
     *
     * @param index index of the element to return
     * @return reference to the element at the index.
     */
    reference operator[](size_t index) throw ();

    /**
     * Returns true if this ArrayList is equal to rhs and false otherwise
     * This operation provides strong exception safety.
     *
     * @param rhs
     * @return
     */
    bool operator==(const ArrayList<T>& rhs) const;

    /**
     * Returns false if this ArrayList is equal to rhs and true otherwise
     * This operation provides strong exception safety.
     *
     * @param rhs
     * @return
     */
    bool operator!=(const ArrayList<T>& rhs) const;

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
     * Returns true if this ArrayList is empty and false otherwise.
     * This operation is a no-throw.
     *
     * @return
     */
    bool isEmpty() const throw ();

    /**
     * Removes and returns the element at the specified index. If index is out
     * of bounds, an std::out_of_range exception is thrown with index as its
     * message. If index points to the last element, this operation is performed
     * in constant time. Otherwise, time proportional to the size of this
     * ArrayList is needed. If reallocation is necessary, the physical capacity
     * remains constant.
     * This operation provides strong exception safety.
     *
     * @param index index of the object to remove.
     * @return copy of the just removed object.
     */
    value_type remove(size_t index);

    /**
     * Sets the element at the specified index to the provided value. If index
     * is out of bounds, an std::out_of_range exception is thrown with the index
     * as its message. This method completes in constant time.
     * This operation provides no exception safety.
     */
    void set(size_t index, const_reference value);


    /**
     * Return the size of this ArrayList.
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
     * Swaps the contents of this ArrayList with that of other in constant time.
     * This operation is a no-throw.
     *
     * @param other the ArrayList to swap with
     */
    void swap(ArrayList<T>& other) throw ();

    size_t mSize;
    size_t mCapacity;
    ScopedArray<T> mArray;
};

#include "../src/ArrayList.cpp"

#endif
