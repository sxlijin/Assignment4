#ifndef _ARRAY_LIST_CPP_
#define _ARRAY_LIST_CPP_

#include "../include/ArrayList.h"
#include "../include/ScopedArray.h"
#include "../include/ArrayListIterators.h"
#include <cstdlib>                  // For size_t
#include <stdexcept>                // For std::out_of_range
#include <sstream>                  // For std::ostringstream
#include <algorithm>


/**
 * Initializes the ArrayList with size elements all set to value. If size is
 * not supplied, an empty ArrayList is created. If value is not supplied,
 * the default value for the parametrized type will be used.
 * This operation provides strong exception safety.
 *
 * @param size size of the ArrayList to create
 * @param value value used to fill the ArrayList
 */
template <typename T>
ArrayList<T>::ArrayList(size_t size, const_reference value)
        : mSize(size), mCapacity(size * 2), mArray(new T[mCapacity]) {
    std::fill(begin(), end(), value);
}

/**
 * Initializes the ArrayList to be a copy of src. Only the logical values of
 * src are copied. This means that any excess capacity of src is ignored.
 * This operation provides strong exception safety.
 *
 * @param src ArrayList to copy
 */
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& src)
        : mSize(src.mSize), mCapacity(src.mSize), mArray(new T[mCapacity]) {
    std::copy(src.begin(), src.end(), begin());
}

/**
 * Makes this object a copy of rhs using the same guidelines as the copy
 * constructor. Note that calling this method on yourself (a = a;) is
 * equivalent to a no-op.
 * This operation provides strong exception safety.
 *
 * @param src ArrayList to copy
 * @return *this, used for chaining.
 */
template <typename T>
const ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs) {
    if (this != &rhs) {
        ArrayList<T> copy(rhs);
        swap(copy);
    }
    return *this;
}

/**
 * Adds value to the end of this ArrayList. If we have excess capacity,
 * the insertion is performed in constant time. Otherwise, time proportional
 * to the size of this ArrayList is needed.
 * This operation provides strong exception safety.
 *
 * @param value value to append to this ArrayList
 */
template <typename T>
void ArrayList<T>::add(const_reference value) {
    if (mSize >= mCapacity) {                   // If need more space
        ScopedArray<T> temp(new T[2 * mSize + 2]);
        std::copy(begin(), end(), temp.get());
        mArray.swap(temp);
        mCapacity = 2 * mSize + 2;
    }

    mArray[mSize] = value;
    ++mSize;
}

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
template <typename T>
void ArrayList<T>::add(size_t index, const_reference value) {
    size_t newSize = std::max(index, mSize) + 1;
    size_t newCap = 2 * newSize;

    ScopedArray<T> temp(new T[newCap]);
    std::copy(begin(), begin() + std::min(index, mSize), temp.get());

    if (index < mSize)
        std::copy(begin() + index, end(), temp.get() + index + 1);
    else
        std::fill(temp.get() + mSize, temp.get() + index, value_type());

    temp[index] = value;
    mArray.swap(temp);
    std::swap(mSize, newSize);
    std::swap(mCapacity, newCap);
}

/**
 * Empties this ArrayList releasing all of its resources (i.e., returning
 * This operation is no-throw under the assumption that the parametrizing
 * type's destructor is no-throw.
 */
template <typename T>
void ArrayList<T>::clear() throw () {
    ArrayList<T> empty;
    swap(empty);
}

/**
 * Returns a constant reference to the element stored at the provided index.
 * If index is out of bounds, an std::out_of_range exception is thrown with
 * the index as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return constant reference to the element at the index.
 */
template <typename T>
typename ArrayList<T>::const_reference ArrayList<T>::get(size_t index) const throw (std::out_of_range) {
    rangeCheck(index);
    return mArray[index];
}

/**
 * Returns a reference to the element stored at the provided index. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message.
 * This operation provides strong exception safety.
 *
 * @param index index of the element to return
 * @return reference to the element at the index.
 */
template <typename T>
typename ArrayList<T>::reference ArrayList<T>::get(size_t index) throw (std::out_of_range) {
    rangeCheck(index);
    return mArray[index];
}

/**
 * Returns a constant reference to the element stored at the provided index.
 * No range checking is performed on the index.
 * This operation is no-throw.
 *
 * @param index index of the element to return
 * @return constant reference to the element at the index.
 */
template <typename T>
typename ArrayList<T>::const_reference ArrayList<T>::operator[](size_t index) const throw () {
    return mArray[index];
}

/**
 * Returns a reference to the element stored at the provided index. No range
 * checking is performed on the index.
 * This operation is no-throw.
 *
 * @param index index of the element to return
 * @return reference to the element at the index.
 */
template <typename T>
typename ArrayList<T>::reference ArrayList<T>::operator[](size_t index) throw () {
    return mArray[index];
}

/**
 * Returns true if this ArrayList is equal to rhs and false otherwise
 * This operation provides strong exception safety.
 *
 * @param rhs
 * @return
 */
template <typename T>
bool ArrayList<T>::operator==(const ArrayList<T>& rhs) const {
    return mSize == rhs.mSize && std::equal(begin(), end(), rhs.begin());
}

/**
 * Returns false if this ArrayList is equal to rhs and true otherwise
 * This operation provides strong exception safety.
 *
 * @param rhs
 * @return
 */
template <typename T>
bool ArrayList<T>::operator!=(const ArrayList<T>& rhs) const {
    return !(*this == rhs);
}

/**
 * Returns a constant iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::begin() const throw () {
    return const_iterator(mArray.get());
}

/**
 * Returns an iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::begin() throw () {
    return iterator(mArray.get());
}

/**
 * Returns a constant iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::end() const throw () {
    return const_iterator(mArray.get() + mSize);
}

/**
 * Returns an iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::end() throw () {
    return iterator(mArray.get() + mSize);
}

/**
 * Returns true if this ArrayList is empty and false otherwise.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
bool ArrayList<T>::isEmpty() const throw () {
    return mSize == 0;
}

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
template <typename T>
typename ArrayList<T>::value_type ArrayList<T>::remove(size_t index) {
    rangeCheck(index);

    value_type result = mArray[index];
    if (index < mSize - 1) {
        ScopedArray<T> temp(new T[mCapacity]);
        std::copy(begin(), begin() + index, temp.get());
        std::copy(begin() + index + 1, end(), temp.get() + index);
        mArray.swap(temp);
    }

    --mSize;
    return result;
}

/**
 * Sets the element at the specified index to the provided value. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message. This method completes in constant time.
 * This operation provides no exception safety.
 */
template <typename T>
void ArrayList<T>::set(size_t index, const_reference value) {
    rangeCheck(index);
    mArray[index] = value;
}

/**
 * Return the size of this ArrayList.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
size_t ArrayList<T>::size() const throw () {
    return mSize;
}

/**
 * Given an index, this method throws an std::out_of_range with the index as
 * its message if index is out of bounds or is a no-op otherwise.
 * This operation provides strong exception safety.
 *
 * @param index index to check
 */
template <typename T>
void ArrayList<T>::rangeCheck(size_t index) const throw (std::out_of_range) {
    if (index >= mSize) {
        std::ostringstream os;
        os << index;
        throw std::out_of_range(os.str());
    }
}

/**
 * Swaps the contents of this ArrayList with that of other in constant time.
 * This operation is a no-throw.
 *
 * @param other the ArrayList to swap with
 */
template <typename T>
void ArrayList<T>::swap(ArrayList<T>& other) throw () {
    std::swap(mSize, other.mSize);
    std::swap(mCapacity, other.mCapacity);
    mArray.swap(other.mArray);
}

#endif
