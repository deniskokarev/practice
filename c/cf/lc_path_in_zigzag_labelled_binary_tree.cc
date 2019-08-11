#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/* https://leetcode.com/contest/weekly-contest-143/problems/path-in-zigzag-labelled-binary-tree/ */

using namespace std;

class Solution {
public:
	static vector<int> pathInZigZagTree(int label) {
		constexpr int MX = (1<<20)+1;
		vector<int> tree(MX);
		for (int i=0; i<MX; i++)
			tree[i] = i;
		for (int i=1; i<20; i++) {
			int b = 1<<i;
			int e = b*2;
			if (i&1)
				reverse(tree.begin()+b, tree.begin()+e);
		}
		vector<int> res;
		int l = 0;
		for (int i=0; i<tree.size(); i++)
			if (tree[i] == label)
				l = i;
		while (l>0) {
			res.push_back(tree[l]);
			l /= 2;
		}
		reverse(res.begin(), res.end());
		for (auto r:res)
			cerr << r << "\n";
		return res;
	}
};

int main(int argc, char **argv) {
	//Solution::pathInZigZagTree(14);
	//Solution::pathInZigZagTree(26);
	//Solution::pathInZigZagTree(2);
	Solution::pathInZigZagTree(1117);
	return 0;
}
