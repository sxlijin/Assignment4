/*
 * G. Hemingway @2016
 */
#include "tests.h"
#include "../include/StackBase.h"
#include "../include/StackAdapter.h"
#include "../include/ArrayList.h"
#include "../include/LinkedList.h"


StackBase<int>* makeIntStack(const int &testMode) {
    switch (testMode) {
        case CREATE_LINKED_STACK:
            return new StackAdapter<LinkedList<int> >;
        case CREATE_ARRAY_STACK:
            return new StackAdapter<ArrayList<int> >;
        default:
            return 0;
    }
}

// The fixture for testing Stack adapter.
class StackTest : public ::testing::Test, public ::testing::WithParamInterface<int> {
#ifdef GRADUATE_STUDENT
    virtual void SetUp() {
        // Graduate student code must preallocate some space in the memory pool
        if (GetParam() == CREATE_LINKED_STACK) {
            LinkedListNode<int>::addToPool(100);
        }
    }

    virtual void TearDown() {
        // Graduate student code must deallocate the memory space in the memory pool
        if (GetParam() == CREATE_LINKED_STACK) {
            LinkedListNode<int>::clearPool();
        }
    }
#endif
};


TEST_P(StackTest, Empty) {
    EXPECT_NO_THROW({
        StackBase<int>* stack = makeIntStack(GetParam());
        EXPECT_TRUE(stack->isEmpty());
        EXPECT_EQ(stack->size(), 0UL);

        EXPECT_THROW({
                 stack->pop();
         }, StackBase<int>::Underflow);

        EXPECT_THROW({
                 stack->top();
         }, StackBase<int>::Underflow);
        delete stack;
    });
}

TEST_P(StackTest, Push) {
    EXPECT_NO_THROW({
        StackBase<int>* stack = makeIntStack(GetParam());
        for (int i = 1; i < 999; ++i) {
            stack->push(i);
            EXPECT_EQ(stack->size(), (size_t) i);
            EXPECT_FALSE(stack->isEmpty());
        }
        delete stack;
    });
}

TEST_P(StackTest, Top) {
    EXPECT_NO_THROW({
        StackBase<int>* stack = makeIntStack(GetParam());
        const StackBase<int>* constStack = stack;
        for (int i = 1; i < 999; ++i) {
            stack->push(i);
            EXPECT_EQ(constStack->top(), i);
            stack->top() = 0;
            EXPECT_EQ(constStack->top(), 0);
        }
        delete stack;
    });
}

TEST_P(StackTest, Pop) {
    EXPECT_NO_THROW({
        StackBase<int>* stack = makeIntStack(GetParam());
        const StackBase<int>* constStack = stack;
        for (int i = 1; i < 999; ++i)
            stack->push(i);
        for (int i = 998; i >= 2; --i) {
            EXPECT_EQ(constStack->top(), i);
            stack->pop();
            EXPECT_EQ(stack->size(), (size_t) i - 1);
            EXPECT_FALSE(stack->isEmpty());
        }
        stack->pop();
        EXPECT_TRUE(stack->isEmpty());
        EXPECT_EQ(stack->size(), 0UL);
        EXPECT_THROW({
                 stack->pop();
         }, StackBase<int>::Underflow);
        delete stack;
    });
}

TEST_P(StackTest, Adapter) {
    EXPECT_NO_THROW({
        StackBase<int>* stack = new StackAdapter<EnforcedIntAdaptee>;
        const StackBase<int>* constStack = stack;
        for (int i = 1; i < 999; ++i)
            stack->push(i);
        for (int i = 998; i >= 2; --i) {
            EXPECT_EQ(constStack->top(), i);
            stack->pop();
            EXPECT_EQ(stack->size(), (size_t) i - 1);
            EXPECT_FALSE(stack->isEmpty());
        }

        stack->pop();
        EXPECT_TRUE(stack->isEmpty());
        EXPECT_EQ(stack->size(), 0UL);

        EXPECT_THROW({
            stack->pop();
        }, StackBase<int>::Underflow);
        delete stack;

    });
}

INSTANTIATE_TEST_CASE_P(Default,
    StackTest,
    ::testing::Values(CREATE_LINKED_STACK, CREATE_ARRAY_STACK),
    ::testing::PrintToStringParamName()
);
