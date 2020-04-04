/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void flatten_dfs(vector<int> &flat, const TreeNode* root) {
        if (root) {
            flatten_dfs(flat, root->left);
            flat.push_back(root->val);
            flatten_dfs(flat, root->right);
        }
    }
    TreeNode *build(const vector<int> &flat, int b, int e) {
        int sz = (e-b);
        if (sz > 0) {
            int m = b+sz/2;
            TreeNode *root = new TreeNode(flat[m]);
            root->left = build(flat, b, m);
            root->right = build(flat, m+1, e);
            return root;
        } else {
            return 0;
        }
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> flat;
        flatten_dfs(flat, root);
        return build(flat, 0, flat.size());
    }
};
