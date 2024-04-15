// https://leetcode.com/problems/sum-root-to-leaf-numbers
class Solution {
    static int dfs(const TreeNode* node, int up) {
        if (node) {
            int down = up * 10 + node->val;
            if (!node->left && !node->right) {
                return down;
            } else {
                return dfs(node->left, down) + dfs(node->right, down);
            }
        } else {
            return 0;
        }
    }
public:
    static int sumNumbers(const TreeNode* root) {
        return dfs(root, 0);
    }
};


class Solution {
    static inline bool is_leaf(const TreeNode* root) {
        return !root->left && !root->right;
    }
    static void dfs(const TreeNode* root, int &sm, int n) {
        if (root) {
            int v = 10 * n + root->val;
            if (is_leaf(root)) {
                sm += v;
            } else {
                dfs(root->left, sm, v);
                dfs(root->right, sm, v);
            }
        }
    }
public:
    int sumNumbers(TreeNode* root) {
        int sm = 0;
        dfs(root, sm, 0);
        return sm;
    }
};
