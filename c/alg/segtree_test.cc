#include "segtree.hh"
#include "gtest/gtest.h"

TEST(SegmentTree, SegmentTreeSum) {
	for (int sz=1; sz<128; sz++) {
		SegmentTree<int> sum(sz);
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

TEST(SegmentTree, SegmentTreeMax) {
	for (int sz=1; sz<128; sz++) {
		SegmentTree<int> max(sz, [](int a, int b){return (a>b)?a:b;});
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
