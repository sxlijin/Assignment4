#ifndef _LINKED_LIST_CPP_
#define _LINKED_LIST_CPP_

#include "../include/LinkedList.h"
#include "../include/LinkedListIterators.h"
#include <cstdlib>          // For size_t
#include <stdexcept>        // For out_of_range
#include <sstream>          // For ostringstream
#include <algorithm>


/**
 * Initializes an empty LinkedList.
 * This operation provides strong exception safety.
 */
template <typename T>
LinkedList<T>::LinkedList() : mSize(0), mTail(new LinkedListNode<T>()) {
}

/**
 * Initializes the LinkedList to be a copy of src.
 * This operation provides strong exception safety.
 *
 * @param src LinkedList to copy
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& src) : mSize(0), mTail(new LinkedListNode<T>()) {
    LinkedList<T> temp;
    for (const_iterator iter = src.begin(); iter != src.end(); ++iter)
        temp.add(*iter);
    swap(temp);
}

/**
 * Makes this object a copy of rhs using the same guidelines as the copy
 * constructor. Note that calling this method on yourself (l = l;) is
 * equivalent to a no-op.
 * This operation provides strong exception safety.
 *
 * @param rhs LinkedList to copy
 * @return *this, used for chaining.
 */
template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this != &rhs) {
        LinkedList<T> copy(rhs);
        swap(copy);
    }
    return *this;
}

/**
 * Destructor. Releases all resources held by this LinkedList.
 * This operation is no-throw under the assumption that the parametrizing
 * type's destructor is no-throw.
 */
template <typename T>
LinkedList<T>::~LinkedList() throw () {
    while (!isEmpty())
        removeNode(begin());
    // mTail cleans up after itself
}

/**
 * Adds value to the end of this LinkedList. The insertion is performed in
 * constant time.
 * This operation provides strong exception safety.
 *
 * @param value value to append to this LinkedList
 */
template <typename T>
void LinkedList<T>::add(const_reference value) {
    new LinkedListNode<T>(value, mTail->mPrev, mTail.get());
    ++mSize;
}

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
template <typename T>
void LinkedList<T>::add(size_t index, const_reference value) {
    if (index < mSize) {    // If inserting into a list
        iterator iter = begin();
        std::advance(iter, index);  // iter now points to the node to be shifted
        new LinkedListNode<T>(value, iter.mPtr->mPrev, iter.mPtr);
        ++mSize;
    } else {                // If need to create new nodes
        LinkedList<T> temp;
        for (size_t i = size(); i < index; ++i)     // Add the necessary default
            temp.add(value_type());                 // nodes
        temp.add(value);                            // Add the value

        // Relink the nodes of the two lists and update sizes
        LinkedListNode<T>* curLast = mTail->mPrev;
        LinkedListNode<T>* tempFirst = temp.mTail->mNext;
        LinkedListNode<T>* tempLast = temp.mTail->mPrev;

        LinkedListNode<T>::link(curLast, tempFirst);
        LinkedListNode<T>::link(tempLast, mTail.get());
        LinkedListNode<T>::link(temp.mTail.get(), temp.mTail.get());

        mSize = index + 1;
        temp.mSize = 0;
    }
}

/**
 * Empties this LinkedList returning it to the same state as the default
 * constructor.
 * This operation is no-throw under the assumption that the parametrizing
 * type's destructor is no-throw.
 */
template <typename T>
void LinkedList<T>::clear() throw () {
    LinkedList<T> empty;
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
typename LinkedList<T>::const_reference LinkedList<T>::get(size_t index) const throw (std::out_of_range) {
    rangeCheck(index);
    const_iterator iter = begin();
    std::advance(iter, index);
    return *iter;
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
typename LinkedList<T>::reference LinkedList<T>::get(size_t index) throw (std::out_of_range) {
    rangeCheck(index);
    iterator iter = begin();
    std::advance(iter, index);
    return *iter;
}

/**
 * Returns true if this LinkedList is equal to rhs and false otherwise
 * This operation provides strong exception safety.
 *
 * @param rhs
 * @return
 */
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    return mSize == rhs.mSize && std::equal(begin(), end(), rhs.begin());
}

/**
 * Returns false if this LinkedList is equal to rhs and true otherwise
 * This operation provides strong exception safety.
 *
 * @param rhs
 * @return
 */
template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const {
    return !(*this == rhs);
}

/**
 * Returns a constant iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const throw () {
    return const_iterator(mTail->mNext);
}

/**
 * Returns an iterator to the beginning.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() throw () {
    return iterator(mTail->mNext);
}

/**
 * Returns a constant iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const throw () {
    return const_iterator(mTail.get());
}

/**
 * Returns an iterator to the end.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() throw () {
    return iterator(mTail.get());
}

/**
 * Returns true if this LinkedList is empty and false otherwise.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
bool LinkedList<T>::isEmpty() const throw () {
    return mSize == 0;
}

/**
 * Removes the element at the specified index. If index is out of bounds
 * an std::out_of_range exception is thrown with index as its messaged. If
 * index points to the first or last element, this operation is performed in
 * constant time. Otherwise, time proportional to index is needed.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to remove.
 */
template <typename T>
void LinkedList<T>::remove(size_t index) throw (std::out_of_range) {
    rangeCheck(index);
    iterator iter = begin();
    std::advance(iter, index);
    removeNode(iter);
}

/**
 * Sets the element at the specified index to the provided value. If index
 * is out of bounds, an std::out_of_range exception is thrown with the index
 * as its message. This method completes in time proportional to index.
 * This operation provides strong exception safety.
 *
 * @param index index of the object to set
 * @param value the new value
 */
template <typename T>
void LinkedList<T>::set(size_t index, const_reference value) {
    rangeCheck(index);
    iterator iter = begin();
    std::advance(iter, index);

    LinkedListNode<T>* oldNode = iter.mPtr;
    new LinkedListNode<T>(value, oldNode->mPrev, oldNode->mNext);
    LinkedListNode<T>::link(oldNode, oldNode);
    delete oldNode;
}

/**
 * Return the size of this LinkedList.
 * This operation is a no-throw.
 *
 * @return
 */
template <typename T>
size_t LinkedList<T>::size() const throw () {
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
void LinkedList<T>::rangeCheck(size_t index) const throw (std::out_of_range) {
    if (index >= mSize) {
        std::ostringstream stream;
        stream << index;
        throw std::out_of_range(stream.str());
    }
}

/**
 * Removes from this LinkedList the node pointed to by iter.
 * This operation is no-throw under the assumption that the parametrizing
 * type's destructor is no-throw.
 *
 * @param iter iterator pointing to the node that should be removed.
 */
template <typename T>
void LinkedList<T>::removeNode(iterator iter) throw () {
    delete iter.mPtr;
    --mSize;
}

/**
 * Swaps the contents of this LinkedList with that of other in constant time.
 * This operation is a no-throw.
 *
 * @param other the LinkedList to swap with
 */
template <typename T>
void LinkedList<T>::swap(LinkedList<T>& other) throw () {
    std::swap(mSize, other.mSize);
    LinkedListNode<T>* myTail = mTail.release();
    mTail.reset(other.mTail.release());
    other.mTail.reset(myTail);
}



/**
 * Initializes this node to store the provided item. The next and previous
 * pointers of this node are set to point to the node itself.
 * This operation provides strong exception safety.
 *
 * @param item the item to set
 */
template <typename T>
LinkedListNode<T>::LinkedListNode(const T& item) : mItem(item), mPrev(this), mNext(this){
}

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
template <typename T>
LinkedListNode<T>::LinkedListNode(const T& item, LinkedListNode<T>* prev, LinkedListNode<T>* next)
        : mItem(item), mPrev(prev), mNext(next) {
    LinkedListNode<T>::link(mPrev, this);
    LinkedListNode<T>::link(this, mNext);
}

/**
 * Destructor. Unlinks this node from its neighbors.
 * This operation is a no-throw.
 */
template <typename T>
LinkedListNode<T>::~LinkedListNode() throw () {
    LinkedListNode<T>::link(mPrev, mNext);
}

template <typename T>
void LinkedListNode<T>::link(LinkedListNode<T>* first, LinkedListNode<T>* second) {
    first->mNext = second;
    second->mPrev = first;
}

/************* Insert Graduate Student code for Memory Pools Here ***********************/
#ifdef GRADUATE_STUDENT


#endif

#endif
