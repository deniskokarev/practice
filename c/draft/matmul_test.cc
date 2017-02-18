#include "gtest/gtest.h"
#include "matmul.hh"

using namespace mm;

TEST(MatMul, T1) {
	std::vector<Mat> m {{30,35}, {35,15}, {15,5}, {5,10}, {10,20}, {20,25}};
	std::vector<std::vector<MultPlan>> plan;
	auto res = optimalMulPlan(m.begin(), m.end(), plan);
	EXPECT_EQ(15125, plan[res.first][res.second].cost);
}
