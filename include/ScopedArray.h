#ifndef _SCOPED_ARRAY_H_
#define _SCOPED_ARRAY_H_
// TODO comment

#include <algorithm>        // For std::swap

template <typename T>
class ScopedArray {
public:

    explicit ScopedArray(T* ptr = 0) : mPtr(ptr) {}

    ~ScopedArray() {
        delete[] mPtr;
    }

    T* release() {
        T* ptr = mPtr;
        mPtr = 0;
        return ptr;
    }

    void reset(T* ptr = 0) {
        delete[] mPtr;
        mPtr = ptr;
    }

    T& operator[](size_t index) const {
        return mPtr[index];
    }

    operator bool() const {
        return mPtr;
    }

    T* get() const {
        return mPtr;
    }

    void swap(ScopedArray& other) {
        std::swap(mPtr, other.mPtr);
    }

private:

    ScopedArray(const ScopedArray&);
    void operator=(const ScopedArray& rhs);

    T* mPtr;
};

#endif  // _SCOPED_ARRAY_H_
