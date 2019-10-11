#include <iostream>
#include <vector>
/* https://leetcode.com/contest/weekly-contest-132/problems/recover-a-tree-from-preorder-traversal/ */
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct N {
	int v;
	int d;
};

class Solution {
public:
    static TreeNode* recoverFromPreorder(string S) {
		vector<N> ss; // (node,depth)
		int dep = 0;
		int b = 0;
		int w = 1;
		int i;
		for (i=0; i<S.size(); i++) {
			if (S[i] == '-') {
				if (w) {
					ss.push_back(N{std::stoi(S.substr(b, i-b)), dep});
					dep = 0;
					w = 0;
				}
				dep++;
			} else {
				if (!w)
					b = i;
				w = 1;
			}
		}
		ss.push_back(N{std::stoi(S.substr(b, i-b)), dep});
		ss.push_back(N{-1,-1});
#if 0
		for (auto &s:ss)
			cerr << "s.str=" << s.first << " s.dep=" << s.second << "\n";
#endif
		TreeNode t(-1);
		int nxt = 0;
		recover_r(ss, &t, &nxt, 0);
		return t.left;
	}
	static void recover_r(const vector<N> &ss, TreeNode *root, int *nxt, int depth) {
		if (ss[*nxt].d < depth)
			return;
		root->left = new TreeNode(ss[*nxt].v);
		(*nxt)++;
		recover_r(ss, root->left, nxt, depth+1);
		if (ss[*nxt].d < depth)
			return;
		root->right = new TreeNode(ss[*nxt].v);
		(*nxt)++;
		recover_r(ss, root->right, nxt, depth+1);
	}
};

void test1() {
	Solution::recoverFromPreorder("1-2--3--4-5--6--7");
}

int main(int argc, char **argv) {
	test1();
	return 0;
}
