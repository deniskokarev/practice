/* TopCoder https://arena.topcoder.com/... */
#include "gtest/gtest.h"

using namespace std;

class MyClass {
public:
	static string myMethod() {
		return "real answer";
	}
};

TEST(TC_TEST, TC0) {
	string expected = "real answer";
	EXPECT_EQ(expected, MyClass::myMethod());
}
