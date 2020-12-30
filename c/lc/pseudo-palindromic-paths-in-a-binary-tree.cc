class Solution {
	bool odd(int n) {
		return n&1;
	}
	void ppaths_r(int &sm, const TreeNode* root, int cnt[10], int no, int dep) {
		if (root) {
			int v = root->val;
			no -= odd(cnt[v]);
			cnt[v]++;
			no += odd(cnt[v]);
			if (!root->left && !root->right) {
				if (odd(dep) && no == 1)
					sm++;
				else if (!odd(dep) && no == 0)
					sm++;
			} else {
				ppaths_r(sm, root->left, cnt, no, dep+1);
				ppaths_r(sm, root->right, cnt, no, dep+1);
			}
			cnt[v]--;
		}
	}
public:
	int pseudoPalindromicPaths(const TreeNode* root) {
		int sm = 0;
		int cnt[10]{0};
		ppaths_r(sm, root, cnt, 0, 1);
		return sm;
	}
};

