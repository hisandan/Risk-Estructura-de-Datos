// test_runner.cpp
#include <gtest/gtest.h>

// test files
#include "general.cpp"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}