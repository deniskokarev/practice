#include "gtest/gtest.h"
#include "lcs.hh"
#include <list>

TEST(LCSTest, T0) {
	const char *a = "1";
	const char *b = "1";
	std::pair<size_t,size_t> res[2];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(1U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(1U, rc2);
}

TEST(LCSTest, T1) {
	const char *a = "1";
	const char *b = "2";
	std::pair<size_t,size_t> res[2];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(0U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0U, rc2);
}

TEST(LCSTest, T2) {
	const char *a = "";
	const char *b = "2";
	std::pair<size_t,size_t> res[2];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(0U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0U, rc2);
}

TEST(LCSTest, T3) {
	const char *a = "1";
	const char *b = "";
	std::pair<size_t,size_t> res[2];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(0U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0U, rc2);
}

TEST(LCSTest, T4) {
	const char *a = "";
	const char *b = "";
	std::pair<size_t,size_t> res[2];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(0U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(0U, rc2);
}

TEST(LCSTest, T5) {
	const char *a = "10203040506070";
	const char *b = "91929394959697912";
	std::pair<size_t,size_t> res[128];
	size_t rc1 = lcs::lcs(a, a+strlen(a), b, b+strlen(b), res);
	EXPECT_EQ(7U, rc1);
	size_t rc2 = lcs::lcs(a, a+strlen(a), b, b+strlen(b));
	EXPECT_EQ(7U, rc2);
	std::string s;
	for (size_t i=0; i<rc1; i++)
		s += a[res[i].first];
	EXPECT_EQ(s, "1234567");
}

TEST(LCSTest, T6) {
	std::string a("0123456789");
	std::string b("0123456789");
	std::vector<std::pair<size_t,size_t>> res;
	size_t rc1 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
	EXPECT_EQ(10U, rc1);
	size_t rc2 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(10U, rc2);
	std::string s;
	for (auto p:res)
		s += a[p.first];
	EXPECT_EQ(s, "0123456789");
}

TEST(LCSTest, T7) {
	std::string a("thisisatest");
	std::string b("testing123testing");
	std::vector<std::pair<size_t,size_t>> res;
	size_t rc1 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
	EXPECT_EQ(7U, rc1);
	size_t rc2 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(7U, rc2);
	std::string s;
	for (auto p:res)
		s += a[p.first];
	EXPECT_EQ(s, "tsitest");
}

TEST(LCSTest, T8) {
	std::list<size_t> a {1, 2, 3, 4, 1};
	std::list<size_t> b {3, 4, 1, 2, 1, 3};
	std::list<std::pair<size_t,size_t>> res;
	size_t rc1 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
	EXPECT_EQ(3U, rc1);
	size_t rc2 = lcs::lcs(a.begin(), a.end(), b.begin(), b.end());
	EXPECT_EQ(3U, rc2);
}
