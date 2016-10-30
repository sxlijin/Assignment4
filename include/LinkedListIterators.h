#ifndef _LINKED_LIST_ITERATORS_H_
#define _LINKED_LIST_ITERATORS_H_

#include <iterator>
#include "LinkedList.h"

template <typename T>
class LinkedListIterator : public std::iterator<std::forward_iterator_tag, T> {
private:

    friend class LinkedList<T>;
    LinkedListNode<T>* mPtr;

    explicit LinkedListIterator(LinkedListNode<T>* ptr) : mPtr(ptr) {}

public:

    LinkedListIterator() : mPtr(0) {}

    bool operator==(const LinkedListIterator<T>& rhs) const {
        return mPtr == rhs.mPtr;
    }

    bool operator!=(const LinkedListIterator<T>& rhs) const {
        return !(*this == rhs);
    }

    T& operator*() {
        return mPtr->mItem;
    }

    const T& operator*() const {
        return mPtr->mItem;
    }

    T* operator->() {
        return &mPtr->mItem;
    }

    const T* operator->() const {
        return &mPtr->mItem;
    }

    LinkedListIterator<T>& operator++() {
        mPtr = mPtr->mNext;
        return *this;
    }

    LinkedListIterator<T> operator++(int) {
        LinkedListIterator<T> copy(*this);
        ++*this;
        return copy;
    }
};

template <typename T>
class LinkedListConstIterator : public std::iterator<std::forward_iterator_tag, T> {
private:

    friend class LinkedList<T>;
    LinkedListNode<T>* mPtr;

    explicit LinkedListConstIterator(LinkedListNode<T>* ptr) : mPtr(ptr) {}

public:

    LinkedListConstIterator() : mPtr(0) {}

    bool operator==(const LinkedListConstIterator<T>& rhs) const {
        return mPtr == rhs.mPtr;
    }

    bool operator!=(const LinkedListConstIterator<T>& rhs) const {
        return !(*this == rhs);
    }

    const T& operator*() const {
        return mPtr->mItem;
    }

    const T* operator->() const {
        return &mPtr->mItem;
    }

    LinkedListConstIterator<T>& operator++() {
        mPtr = mPtr->mNext;
        return *this;
    }

    LinkedListConstIterator<T> operator++(int) {
        LinkedListConstIterator<T> copy(*this);
        ++*this;
        return copy;
    }
};

#endif
