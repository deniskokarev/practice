#include "comb.hh"
#include "gtest/gtest.h"

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(1, fact(1));
  EXPECT_EQ(2, fact(2));
  EXPECT_EQ(6, fact(3));
  EXPECT_EQ(40320, fact(8));
}
