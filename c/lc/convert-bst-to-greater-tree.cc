class Solution {
    void dfs(TreeNode* root, int &sm) {
        if (root) {
            dfs(root->right, sm);
            root->val += sm;
            sm = root->val;
            dfs(root->left, sm);
        }
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        int sm = 0;
        dfs(root, sm);
        return root;
    }
};
