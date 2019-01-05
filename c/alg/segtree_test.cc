#include "segtree.hh"
#include "gtest/gtest.h"
#include <numeric>

TEST(SegTree, Sum0) {
	SegTree<int> sum({1,2,3});
	EXPECT_EQ(sum(), 6);
	sum.set(0, 2);
	sum.set(1, 3);
	sum.set(2, 4);
	EXPECT_EQ(sum(), 9);
}

TEST(SegTree, Sum) {
	for (int sz=1; sz<128; sz++) {
		SegTree<int> sum(sz);
		for (int i=0; i<sz; i++)
			sum.set(i, i);
		for (int w=1; w<sz; w++) {
			for (int i=0; i<sz-w; i++) {
				int arsum = (i+w)*(i+w-1)/2 - i*(i-1)/2;
				EXPECT_EQ(sum(i, i+w), arsum);
			}
		}
	}
}

TEST(SegTree, Max) {
	for (int sz=1; sz<128; sz++) {
		SegTree<int> max(sz, [](int a, int b){return (a>b)?a:b;});
		for (int i=0; i<sz; i++)
			max.set(i, i);
		for (int w=1; w<sz; w++) {
			for (int i=0; i<sz-w; i++) {
				int mx = i+w-1;
				EXPECT_EQ(max(i, i+w), mx);
			}
		}
	}
}

TEST(AddSegTree, Add1) {
	AddSegTree<int> sum({1,2,3});
	sum.add_each(0, 3, 1);
	EXPECT_EQ(std::accumulate(sum.begin(), sum.end(), 0), 9);
}

TEST(AddSegTree, UpIncStat) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=0; i<sz; i++)
			sum.add_each(i, sz, 1);
		std::vector<int> res(sz);
		for (int i=0; i<sz; i++)
			res[i] = i+1;
		EXPECT_EQ(std::equal(res.begin(), res.end(), sum.begin()), true);
	}
}

TEST(AddSegTree, UpIncDyn) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=0; i<sz; i++)
			sum.add_each(i, sz, 1);
		std::vector<int> ans(sz);
		for (int i=0; i<sz; i++)
			ans[i] = sum.get(i);
		std::vector<int> res(sz);
		for (int i=0; i<sz; i++)
			res[i] = i+1;
		EXPECT_EQ(std::equal(res.begin(), res.end(), ans.begin()), true);
	}
}

TEST(AddSegTree, DownIncStat) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=1; i<sz; i++)
			sum.add_each(0, i, 1);
		std::vector<int> res(sz);
		for (int i=0; i<sz; i++)
			res[i] = sz-i-1;
		EXPECT_EQ(std::equal(res.begin(), res.end(), sum.begin()), true);
	}
}

TEST(AddSegTree, DownIncDyn) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=1; i<sz; i++)
			sum.add_each(0, i, 1);
		std::vector<int> ans(sz);
		for (int i=0; i<sz; i++)
			ans[i] = sum.get(i);
		std::vector<int> res(sz);
		for (int i=0; i<sz; i++)
			res[i] = sz-i-1;
		EXPECT_EQ(std::equal(res.begin(), res.end(), ans.begin()), true);
	}
}

TEST(AddSegTree, UpIncHalfSum) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=0; i<=sz/2; i++)
			sum.add_each(i, sz-i, 1);
		int ans = 0;
		for (int i=0; i<sz; i++)
			ans += sum.get(i);
		int s1 = sz/2;
		int s2 = sz-s1;
		int arsum = s1*(s1+1)/2 + s2*(s2+1)/2;
		EXPECT_EQ(ans, arsum);
	}
}

TEST(AddSegTree, DownIncHalfSum) {
	for (int sz=1; sz<128; sz++) {
		AddSegTree<int> sum(sz);
		for (int i=sz/2; i>=0; i--)
			sum.add_each(i, sz-i, 1);
		int ans = 0;
		for (int i=sz-1; i>=0; i--)
			ans += sum.get(i);
		int s1 = sz/2;
		int s2 = sz-s1;
		int arsum = s1*(s1+1)/2 + s2*(s2+1)/2;
		EXPECT_EQ(ans, arsum);
	}
}

