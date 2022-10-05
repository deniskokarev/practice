// https://leetcode.com/problems/add-one-row-to-tree/

enum {L, R};

class Solution {
    TreeNode* dfs(TreeNode* root, int val, int dep, int dir) {
        if (dep == 1) {
            if (dir == L)
                return new TreeNode(val, addOneRow(root, val, dep-1), nullptr);
            else
                return new TreeNode(val, nullptr, addOneRow(root, val, dep-1));
        } else if (root) {
            root->left = dfs(root->left, val, dep-1, L);
            root->right = dfs(root->right, val, dep-1, R);
        }
        return root;
    }
public:
    TreeNode* addOneRow(TreeNode* root, int val, int dep) {
        return dfs(root, val, dep, L);
    }
};
