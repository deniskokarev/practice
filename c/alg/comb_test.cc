#include "comb.hh"
#include "gtest/gtest.h"

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(1U, fact(1));
  EXPECT_EQ(2U, fact(2));
  EXPECT_EQ(6U, fact(3));
  EXPECT_EQ(40320U, fact(8));
}
