class Solution {
    bool check_dfs(const TreeNode* root, vector<int> &last, int lvl) {
        if (root) {
            if ((root->val&1) == (lvl&1))
                return false;
            if (last.size() <= lvl) {
                last.push_back(root->val);
            } else {
                if (lvl&1) {
                    if (root->val >= last[lvl])
                        return false;
                } else {
                    if (root->val <= last[lvl])
                        return false;
                }
                last[lvl] = root->val;
            }
            return check_dfs(root->left, last, lvl+1) && check_dfs(root->right, last, lvl+1);
        } else {
            return true;
        }
    }
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<int> last;
        return check_dfs(root, last, 0);
    }
};

