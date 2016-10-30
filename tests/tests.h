#ifndef _TESTS_H_
#define _TESTS_H_

#include <gtest/gtest.h>


// Couple of global defines
#define  CREATE_LINKED_STACK    1
#define  CREATE_ARRAY_STACK     2

//#define GRADUATE_STUDENT

struct EnforcedIntAdaptee {
    typedef int value_type;

    void add(int x) {
        mData.push_back(x);
    }

    const int& get(size_t index) const {
        return mData[index];
    }

    int& get(size_t index) {
        return mData[index];
    }

    void remove(size_t index) {
        mData.erase(mData.begin() + index);
    }

    size_t size() const {
        return mData.size();
    }

private:
    std::vector<int> mData;
};

#endif //_TESTS_H_
