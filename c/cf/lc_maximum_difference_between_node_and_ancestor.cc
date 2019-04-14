#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-132/problems/maximum-difference-between-node-and-ancestor/ */
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


struct MM {
	int mx, mn;
	int mxdiff;
};

class Solution {
public:
	int maxAncestorDiff(TreeNode* root) {
		MM mymm = MM {root->val, root->val, 0};
		return solve_r(root, mymm);
	}
	int solve_r(TreeNode* root, const MM &mm) {
		MM mymm = MM {
			std::max(mm.mx, root->val),
			std::min(mm.mn, root->val),
			std::max(mm.mxdiff, std::max(std::abs(mm.mx-root->val), std::abs(mm.mn-root->val)))
		};
		if (root->right)
			mymm.mxdiff = solve_r(root->right, mymm);
		if (root->left)
			mymm.mxdiff = solve_r(root->left, mymm);
		return mymm.mxdiff;
	}
};

void test1() {
}

int main(int argc, char **argv) {
	test1();
	return 0;
}
