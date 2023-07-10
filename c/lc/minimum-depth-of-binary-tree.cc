// https://leetcode.com/problems/minimum-depth-of-binary-tree/
class Solution {
    static constexpr int INF = INT_MAX;
    static inline bool is_leaf(const TreeNode* n) {
        return n && !n->left && !n->right;
    }
    static int min_dep_dfs(const TreeNode* n) {
        if (n) {
            if (is_leaf(n)) {
                return 1;
            } else {
                return min(min_dep_dfs(n->left), min_dep_dfs(n->right)) + 1;
            }
        } else {
            return INF;
        }
    }
public:
    static int minDepth(const TreeNode* root) {
        if (root) {
            return min_dep_dfs(root);
        } else {
            return 0;
        }
    }
};
