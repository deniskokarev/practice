//
// a working concept of using kmp on a tree to find downwards sub-path
// unlike 1d kmp, does not have linear complexity, as the above prefix may be backtracked
// upto 2^n_children times
//
class Solution {
	static constexpr int SEP = INT_MIN;
	static bool dfs_match_kmp(const TreeNode* root, int i, int k, vector<int> &str, vector<int> &prefix) {
		if (root) {
			str[i] = root->val;
			for (; k>0 && str[i] != str[k]; k=prefix[k-1]);
			if (str[i] == str[k]) {
				k++;
				prefix[i] = k;
			} else {
				prefix[i] = 0;
			}
			if (str[prefix[i]] == SEP)
				return true;
			return dfs_match_kmp(root->left, i+1, k, str, prefix) || dfs_match_kmp(root->right, i+1, k, str, prefix);
		} else {
			return false;
		}
	}
public:
	static bool isSubPath(const ListNode* head, const TreeNode* root) {
		constexpr int MX = 3000; // length of list + height of tree
		vector<int> str(MX);
		int sz = 0;
		while (head) {
			str[sz++] = head->val;
			head = head->next;
		}
		str[sz++] = SEP;
		vector<int> prefix(MX);
		int k = 0;
		prefix[0] = 0;
		for (size_t i=1; i<sz; i++) {
			for (; k>0 && str[i] != str[k]; k=prefix[k-1]);
			if (str[i] == str[k]) {
				k++;
				prefix[i] = k;
			} else {
				prefix[i] = 0;
			}
		}
		return dfs_match_kmp(root, sz, 0, str, prefix);
	}
};

