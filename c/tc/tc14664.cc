/* TopCoder https://arena.topcoder.com/#/u/practiceCode/17372/56891/14664/2/331921 */
#include "gtest/gtest.h"

using namespace std;

class PlayingWithPlanks {
public:
	static string canItBeDone(int plankLength, int pieces) {
		int mxSz = pieces*(pieces+1)/2;
		if (mxSz <= plankLength)
			return "possible";
		else
			return "impossible";
	}
};

TEST(TC, TC0) {
	EXPECT_EQ("possible", PlayingWithPlanks::canItBeDone(9, 3));
}

TEST(TC, TC1) {
	EXPECT_EQ("possible", PlayingWithPlanks::canItBeDone(12, 1));
}

TEST(TC, TC2) {
	EXPECT_EQ("possible", PlayingWithPlanks::canItBeDone(10, 4));
}

TEST(TC, TC3) {
	EXPECT_EQ("possible", PlayingWithPlanks::canItBeDone(750932, 901));
}

TEST(TC, TC4) {
	EXPECT_EQ("impossible", PlayingWithPlanks::canItBeDone(9, 4));
}

TEST(TC, TC5) {
	EXPECT_EQ("impossible", PlayingWithPlanks::canItBeDone(54, 10));
}
