/*
 * G. Hemingway @2016
 */

#include "tests.h"
#include "../include/QueueBase.h"
#include "../include/QueueAdapter.h"
#include "../include/ArrayList.h"
#include "../include/LinkedList.h"


QueueBase<int>* makeIntQueue(const int &testMode) {
    switch (testMode) {
        case CREATE_LINKED_STACK:
            return new QueueAdapter<LinkedList<int> >;
        case CREATE_ARRAY_STACK:
            return new QueueAdapter<ArrayList<int> >;
        default:
            return 0;
    }
}

// The fixture for testing Queue adapter.
class QueueTest : public ::testing::Test, public ::testing::WithParamInterface<int> {};

TEST_P(QueueTest, Empty) {
    EXPECT_NO_THROW({
        QueueBase<int>* q = makeIntQueue(GetParam());
        EXPECT_TRUE(q->isEmpty());
        EXPECT_EQ(q->size(), 0UL);

        EXPECT_THROW({
                             q->dequeue();
                     }, QueueBase<int>::Underflow);

        delete q;
    });

    EXPECT_NO_THROW({
        QueueBase<int>* q = makeIntQueue(GetParam());
        EXPECT_TRUE(q->isEmpty());
        EXPECT_EQ(q->size(), 0UL);

        EXPECT_THROW({
                             q->front();
                     }, QueueBase<int>::Underflow);

        delete q;
    });
}

TEST_P(QueueTest, Enqueue) {
    EXPECT_NO_THROW({
        QueueBase<int>* q = makeIntQueue(GetParam());
        for (int i = 1; i < 999; ++i) {
            q->enqueue(i);
            EXPECT_EQ(q->size(), (size_t) i);
            EXPECT_FALSE(q->isEmpty());
        }
        delete q;
    });
}

TEST_P(QueueTest, Front) {
    EXPECT_NO_THROW({
        QueueBase<int>* q = makeIntQueue(GetParam());
        const QueueBase<int>* constQ = q;
        for (int i = 1; i < 999; ++i) {
            q->enqueue(i);
            EXPECT_EQ(constQ->front(), 1);
            q->front() = i;
            EXPECT_EQ(constQ->front(), i);
            q->front() = 1;
        }
        delete q;
    });
}

TEST_P(QueueTest, Dequeue) {
    EXPECT_NO_THROW({
        QueueBase<int>* q = makeIntQueue(GetParam());
        const QueueBase<int>* constQ = q;
        for (int i = 1; i < 999; ++i) {
            q->enqueue(i);
        }

        for (int i = 998; i >= 2; --i) {
            EXPECT_EQ(constQ->front(), 999 - i);
            q->dequeue();
            EXPECT_EQ(q->size(), (size_t) i - 1);
            EXPECT_FALSE(q->isEmpty());
        }

        q->dequeue();
        EXPECT_TRUE(q->isEmpty());
        EXPECT_EQ(q->size(), 0UL);
        EXPECT_THROW({
                             q->dequeue();
                     }, QueueBase<int>::Underflow);
        delete q;
    });
}

TEST_P(QueueTest, Adapter) {
    EXPECT_NO_THROW({
        QueueBase<int>* q = new QueueAdapter<EnforcedIntAdaptee>;
        const QueueBase<int>* constQ = q;
        for (int i = 1; i < 999; ++i)
            q->enqueue(i);
        for (int i = 998; i >= 2; --i) {
            EXPECT_EQ(constQ->front(), 999 - i);
            q->dequeue();
            EXPECT_EQ(q->size(), (size_t) i - 1);
            EXPECT_FALSE(q->isEmpty());
        }

        q->dequeue();
        EXPECT_TRUE(q->isEmpty());
        EXPECT_EQ(q->size(), 0UL);

        EXPECT_THROW({
            q->dequeue();
        }, QueueBase<int>::Underflow);
        delete q;
    });
}

INSTANTIATE_TEST_CASE_P(Default,
    QueueTest,
    ::testing::Values(CREATE_LINKED_STACK, CREATE_ARRAY_STACK),
    ::testing::PrintToStringParamName()
);
