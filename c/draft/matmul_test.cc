#include "gtest/gtest.h"
#include "matmul.hh"

using namespace mm;

TEST(MatMul, T1) {
	std::vector<Mat> m {Mat(30, 35), Mat(35, 15), Mat(15, 5), Mat(5, 10), Mat(10, 20), Mat(20, 25)};
	std::vector<std::vector<MultPlan>> plan;
	auto r = optimalMulPlan(m.begin(), m.end(), plan);
	std::cerr << plan[r.first][r.second].cost << std::endl;
}
