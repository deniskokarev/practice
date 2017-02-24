#include "gtest/gtest.h"
#include "lcs.hh"
#include <list>

TEST(LCSTest, T0) {
	const char *a = "1";
	const char *b = "1";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(1, res.size());
}

TEST(LCSTest, T1) {
	const char *a = "1";
	const char *b = "2";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0, res.size());
}

TEST(LCSTest, T2) {
	const char *a = "";
	const char *b = "2";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0, res.size());
}

TEST(LCSTest, T3) {
	const char *a = "1";
	const char *b = "";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0, res.size());
}

TEST(LCSTest, T4) {
	const char *a = "";
	const char *b = "";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0, res.size());
}

TEST(LCSTest, T5) {
	const char *a = "10203040506070";
	const char *b = "91929394959697912";
	std::vector<std::pair<int,int>> res = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(7, res.size());
}

TEST(LCSTest, T6) {
	std::string a("0123456789");
	std::string b("0123456789");
	std::vector<std::pair<int,int>> res = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(10, res.size());
}

TEST(LCSTest, T7) {
	std::string a("thisisatest");
	std::string b("testing123testing");
	std::vector<std::pair<int,int>> res = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(7, res.size());
}

TEST(LCSTest, T8) {
	std::list<int> a {1, 2, 3, 4, 1};
	std::list<int> b {3, 4, 1, 2, 1, 3};
	std::vector<std::pair<int,int>> res = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(3, res.size());
}
