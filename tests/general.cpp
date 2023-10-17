#include <gtest/gtest.h>

// Function to add two numbers
int Add(int a, int b) {
    return a + b;
}

// Test case to verify the Add function
TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(Add(2, 3), 5);
}

TEST(AddTest, NegativeNumbers) {
    EXPECT_EQ(Add(-2, -3), -5);
}

TEST(AddTest, MixedNumbers) {
    EXPECT_EQ(Add(5, -3), 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
