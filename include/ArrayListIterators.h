#ifndef _ARRAY_LIST_ITERATORS_H_
#define _ARRAY_LIST_ITERATORS_H_

#include <iterator>

/**
 * A random access iterator implementation for the ArrayList capable of changing
 * the content it is pointing to. By the virtue of this class's design, all of
 * the methods are guaranteed no-throws and complete in constant-time.
 * Note that this implementation leaves out some less commonly used random
 * iterator methods like the subsript operator and comparison operators.
 *
 * @author Krzysztof Zienkiewicz
 * @date October 1, 2011
 */
template <typename T>
class ArrayListIterator : public std::iterator<std::random_access_iterator_tag, T> {
private:

    friend class ArrayList<T>;
    T* mPtr;

    /**
     * A private explicit constructor used in ArrayList's begin() and end().
     *
     * @param
     */
    explicit ArrayListIterator(T* ptr) : mPtr(ptr) {}

public:

    /**
     * Default constructor. Equivalent to a null pointer.
     */
    ArrayListIterator() : mPtr(0) {}

    /**
     * Equality operator.
     *
     * @param
     * @return
     */
    bool operator==(const ArrayListIterator<T>& rhs) const {
        return mPtr == rhs.mPtr;
    }

    /**
     * Inequality operator.
     *
     * @param
     * @return
     */
    bool operator!=(const ArrayListIterator<T>& rhs) const {
        return !(*this == rhs);
    }

    /**
     * Dereference as an lvalue.
     *
     * @return
     */
    T& operator*() {
        return *mPtr;
    }

    /**
     * Dereference as an rvalue.
     *
     * @return
     */
    const T& operator*() const {
        return *mPtr;
    }

    /**
     * Pointer-style dereference as an rvalue.
     *
     * @return
     */
    T* operator->() {
        return mPtr;
    }

    /**
     * Pointer-style dereference as an rvalue.
     *
     * @return
     */
    const T* operator->() const {
        return mPtr;
    }

    /**
     * Preincrement operator.
     *
     * @return
     */
    ArrayListIterator<T>& operator++() {
        ++mPtr;
        return *this;
    }

    /**
     * Postincrement operator.
     *
     * @return
     */
    ArrayListIterator<T> operator++(int) {
        return ArrayListIterator<T>(mPtr++);
    }

    /**
     * Arithmetic addition
     *
     * @param
     * @return
     */
    ArrayListIterator<T> operator+(int offset) {
        return ArrayListIterator<T>(mPtr + offset);
    }

    /**
     * Arithmetic subtraction
     *
     * @param
     * @return
     */
    ArrayListIterator<T> operator-(int offset) {
        return ArrayListIterator<T>(mPtr - offset);
    }

    /**
     * Iterator subtraction (equivalent to pointer subtraction).
     *
     * @param
     * @return
     */
    int operator-(const ArrayListIterator<T>& rhs) {
        return mPtr - rhs.mPtr;
    }
};

/**
 * Free function to make arithmetic addition commutative.
 *
 * @param
 * @param
 * @return
 */
template <typename T>
ArrayListIterator<T> operator+(int offset, const ArrayListIterator<T>& iter) {
    return iter + offset;
}

/**
 * Free function to make arithmetic subtraction commutative.
 *
 * @param
 * @param
 * @return
 */
template <typename T>
ArrayListIterator<T> operator-(int offset, const ArrayListIterator<T>& iter) {
    return iter - offset;
}


/**
 * A random access iterator implementation for the ArrayList incapable of
 * changing its content. By the virtue of this class's design, all of
 * the methods are guaranteed no-throws and complete in constant-time.
 * Note that this implementation leaves out some less commonly used random
 * iterator methods like the subsript operator and comparison operators.
 *
 * @author Krzysztof Zienkiewicz
 * @date October 1, 2011
 */
template <typename T>
class ArrayListConstIterator : public std::iterator<std::random_access_iterator_tag, T> {
private:

    friend class ArrayList<T>;
    T* mPtr;

    /**
     * A private explicit constructor used in ArrayList's begin() and end().
     *
     * @param
     */
    explicit ArrayListConstIterator(T* ptr) : mPtr(ptr) {}

public:

    /**
     * Default constructor. Equivalent to a null pointer.
     */
    ArrayListConstIterator() : mPtr(0) {}

    /**
     * Equality operator.
     *
     * @param
     * @return
     */
    bool operator==(const ArrayListConstIterator<T>& rhs) const {
        return mPtr == rhs.mPtr;
    }

    /**
     * Inequality operator.
     *
     * @param
     * @return
     */
    bool operator!=(const ArrayListConstIterator<T>& rhs) const {
        return !(*this == rhs);
    }

    /**
     * Dereference as an rvalue.
     *
     * @return
     */
    const T& operator*() const {
        return *mPtr;
    }

    /**
     * Pointer-style dereference as an rvalue.
     *
     * @return
     */
    const T* operator->() const {
        return mPtr;
    }

    /**
     * Preincrement operator.
     *
     * @return
     */
    ArrayListConstIterator<T>& operator++() {
        ++mPtr;
        return *this;
    }

    /**
     * Postincrement operator.
     *
     * @return
     */
    ArrayListConstIterator<T> operator++(int) {
        return ArrayListIterator<T>(mPtr++);
    }

    /**
     * Arithmetic addition
     *
     * @param
     * @return
     */
    ArrayListConstIterator<T> operator+(int offset) {
        return ArrayListConstIterator<T>(mPtr + offset);
    }

    /**
     * Arithmetic subtraction
     *
     * @param
     * @return
     */
    ArrayListConstIterator<T> operator-(int offset) {
        return ArrayListConstIterator<T>(mPtr - offset);
    }

    /**
     * Iterator subtraction (equivalent to pointer subtraction).
     *
     * @param
     * @return
     */
    int operator-(const ArrayListConstIterator<T>& rhs) {
        return mPtr - rhs.mPtr;
    }
};

/**
 * Free function to make arithmetic addition commutative.
 *
 * @param
 * @param
 * @return
 */
template <typename T>
ArrayListConstIterator<T> operator+(int offset, const ArrayListConstIterator<T>& iter) {
    return iter + offset;
}

/**
 * Free function to make arithmetic subtraction commutative.
 *
 * @param
 * @param
 * @return
 */
template <typename T>
ArrayListConstIterator<T> operator-(int offset, const ArrayListConstIterator<T>& iter) {
    return iter - offset;
}

#endif
