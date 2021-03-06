#include "gtest/gtest.h"
#include "knapsack.hh"
// http://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html
TEST(KsNaiveTest, T1) {
	std::vector<ks::Item> items {
		{23, 92},
		{31, 57},
		{29, 49},
		{44, 68},
		{53, 60},
		{38, 43},
		{63, 67},
		{85, 84},
		{89, 87},
		{82, 72}
	};
	int rc = ks::naive(165, items);
	EXPECT_EQ(309, rc);
}

TEST(KsNaiveTest, T2) {
	std::vector<ks::Item> items {
		{41, 442},
		{50, 525},
		{49, 511},
		{59, 593},
		{55, 546},
		{57, 564},
		{60, 617}
	};
	int rc = ks::naive(170, items);
	EXPECT_EQ(1735, rc);
}

TEST(KsBetterTest, T1) {
	std::vector<ks::Item> items {
		{23, 92},
		{31, 57},
		{29, 49},
		{44, 68},
		{53, 60},
		{38, 43},
		{63, 67},
		{85, 84},
		{89, 87},
		{82, 72}
	};
	int rc = ks::better(165, items);
	EXPECT_EQ(309, rc);
}

TEST(KsBetterTest, T2) {
	std::vector<ks::Item> items {
		{41, 442},
		{50, 525},
		{49, 511},
		{59, 593},
		{55, 546},
		{57, 564},
		{60, 617}
	};
	int rc = ks::better(170, items);
	EXPECT_EQ(1735, rc);
}

TEST(KsBetterTest, T3) {
	std::vector<ks::Item> items {
		{70, 135},
		{73, 139},
		{77, 149},
		{80, 150},
		{82, 156},
		{87, 163},
		{90, 173},
		{94, 184},
		{98, 192},
		{106, 201},
		{110, 210},
		{113, 214},
		{115, 221},
		{118, 229},
		{120, 240}
	};
	int rc = ks::better(750, items);
	EXPECT_EQ(1458, rc);
}

TEST(KsDPTest, T1) {
	std::vector<ks::Item> items {
		{23, 92},
		{31, 57},
		{29, 49},
		{44, 68},
		{53, 60},
		{38, 43},
		{63, 67},
		{85, 84},
		{89, 87},
		{82, 72}
	};
	int rc = ks::dp(165, items);
	EXPECT_EQ(309, rc);
}

TEST(KsDPTest, T2) {
	std::vector<ks::Item> items {
		{41, 442},
		{50, 525},
		{49, 511},
		{59, 593},
		{55, 546},
		{57, 564},
		{60, 617}
	};
	int rc = ks::dp(170, items);
	EXPECT_EQ(1735, rc);
}

TEST(KsDPTest, T3) {
	std::vector<ks::Item> items {
		{70, 135},
		{73, 139},
		{77, 149},
		{80, 150},
		{82, 156},
		{87, 163},
		{90, 173},
		{94, 184},
		{98, 192},
		{106, 201},
		{110, 210},
		{113, 214},
		{115, 221},
		{118, 229},
		{120, 240}
	};
	int rc = ks::dp(750, items);
	EXPECT_EQ(1458, rc);
}
