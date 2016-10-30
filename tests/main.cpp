/*
 * G. Hemingway @2016
 */

#include "tests.h"


int main(int argc, char **argv) {
    // Run the registered tests
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
