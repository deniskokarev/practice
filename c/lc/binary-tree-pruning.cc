// https://leetcode.com/problems/binary-tree-pruning/
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root) {
            root->left = pruneTree(root->left);
            root->right = pruneTree(root->right);
            if (root->left || root->right || root->val == 1) {
                return root;
            }
        }
        return NULL;
    }
};
