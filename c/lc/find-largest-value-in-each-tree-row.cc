// https://leetcode.com/problems/find-largest-value-in-each-tree-row
class Solution {
    static void dfs(vector<int> &res, const TreeNode* root, int lvl) {
        if (root) {
            if (res.size() <= lvl) {
                res.push_back(root->val);
            } else {
                res[lvl] = max(res[lvl], root->val);
            }
            dfs(res, root->left, lvl+1);
            dfs(res, root->right, lvl+1);
        }
    }
public:
    static vector<int> largestValues(const TreeNode* root) {
        vector<int> res;
        dfs(res, root, 0);
        return res;
    }
};
