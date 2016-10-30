cmake_minimum_required(VERSION 3.2)
project(Assignment4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -pedantic-errors")

# Include the GoogleTest directory
set(GTEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest/googletest)
# Add GoogleTest as a build subdirectory
add_subdirectory(lib/googletest)
# Include the GoogleTest header directory
include_directories(${GTEST_DIRECTORY}/include)

# Define the source files and dependencies for testing executable
set(SOURCE_FILES tests/main.cpp ${GTEST_DIRECTORY}/include/gtest/gtest.h tests/stackTest.cpp tests/queueTest.cpp)
add_executable(Testing ${SOURCE_FILES})
target_link_libraries(Testing gtest)
