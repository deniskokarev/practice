#include "binomial.hh"
#include "comb.hh"
#include "gtest/gtest.h"

TEST(Binomial, BinomialAll) {
	uint64_t v;
	v = CHOOSE(100000000, 2);
	EXPECT_EQ(100000000ULL*(100000000-1)/2, v);
	v = CHOOSE(1, 1);
	EXPECT_EQ(choose(1, 1), v);
	v = CHOOSE(2, 1);
	EXPECT_EQ(choose(2, 1), v);
	v = CHOOSE(2, 2);
	EXPECT_EQ(choose(2, 2), v);
	v = CHOOSE(3, 1);
	EXPECT_EQ(choose(3, 1), v);
	v = CHOOSE(3, 1);
	EXPECT_EQ(choose(3, 1), v);
	v = CHOOSE(3, 2);
	EXPECT_EQ(choose(3, 2), v);
	v = CHOOSE(3, 3);
	EXPECT_EQ(choose(3, 3), v);
	v = CHOOSE(4, 1);
	EXPECT_EQ(choose(4, 1), v);
	v = CHOOSE(4, 2);
	EXPECT_EQ(choose(4, 2), v);
	v = CHOOSE(4, 3);
	EXPECT_EQ(choose(4, 3), v);
	v = CHOOSE(4, 4);
	EXPECT_EQ(choose(4, 4), v);
	v = CHOOSE(61, 30);
	EXPECT_EQ(choose(61, 30), v);
	v = CHOOSE(61, 61);
	EXPECT_EQ(1, v);
}
