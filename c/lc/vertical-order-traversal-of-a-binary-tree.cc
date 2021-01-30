class Solution {
	void dfs(int &x, int &y, map<int,map<int,multiset<int>>> &ord, const TreeNode* root) {
		if (root) {
			ord[x][y].insert(root->val);
			x -= 1;
			y += 1;
			dfs(x, y, ord, root->left);
			x += 2;
			dfs(x, y, ord, root->right);
			x -= 1;
			y -= 1;
		}
	}
public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {
		map<int,map<int,multiset<int>>> ord;
		int x = 0, y = 0;
		dfs(x, y, ord, root);
		vector<vector<int>> res(ord.size());
		int i = 0;
		for (auto &e:ord) {
			for (auto &ns:e.second)
				for (auto n:ns.second)
					res[i].push_back(n);
			i++;
		}
		return res;
	}
};
