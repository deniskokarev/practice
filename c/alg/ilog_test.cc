#include "ilog.hh"
#include "gtest/gtest.h"
#include <cmath>
#include <climits>

TEST(ILog2Test, HandlesPositiveInput) {
	EXPECT_EQ(0, ilog2(0));
	EXPECT_EQ(0, ilog2((char)1));
	EXPECT_EQ(1, ilog2((int)2));
	EXPECT_EQ(2, ilog2((long)3));
	EXPECT_EQ(2, ilog2((long long)4));
	EXPECT_EQ(3, ilog2((unsigned char)5));
	EXPECT_EQ(3, ilog2((unsigned int)6));
	EXPECT_EQ(3, ilog2((unsigned long)7));
	EXPECT_EQ(3, ilog2((unsigned long long)8));
	EXPECT_EQ(4, ilog2((short)9));
	EXPECT_EQ(4, ilog2((unsigned short)10));
	EXPECT_EQ(64, ilog2(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log2(i))), ilog2(i));
}

TEST(ILog10Test, HandlesPositiveInput) {
	EXPECT_EQ(0, ilog10(0));
	EXPECT_EQ(0, ilog10(1));
	EXPECT_EQ(1, ilog10(2));
	EXPECT_EQ(1, ilog10(9));
	EXPECT_EQ(1, ilog10(10));
	EXPECT_EQ(2, ilog10(11));
	EXPECT_EQ(18, ilog10(1000000000000000000ULL-1));
	EXPECT_EQ(18, ilog10(1000000000000000000ULL));
	EXPECT_EQ(19, ilog10(1000000000000000000ULL+1));
	EXPECT_EQ(20, ilog10(ULLONG_MAX));
	for (auto i=1; i<100002; i++)
		EXPECT_EQ(int(ceil(log10(i))), ilog10(i));
}
