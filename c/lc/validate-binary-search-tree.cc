// https://leetcode.com/problems/validate-binary-search-tree/

class Solution {
    static bool dfs(const TreeNode* root, int64_t &prev) {
        if (root) {
            auto l = dfs(root->left, prev);
            int64_t v = root->val;
            if (l && v > prev) {
                prev = v;
                return dfs(root->right, prev);
            } else {
                return false;
            }
        } else {
            return true;
        }
    }
public:
    static bool isValidBST(const TreeNode* root) {
        int64_t prev = LLONG_MIN;
        return dfs(root, prev);
    }
};
