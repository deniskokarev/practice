// https://leetcode.com/problems/symmetric-tree
class Solution {
    static bool isSymmetric(const TreeNode* l, const TreeNode* r) {
        if (!l && !r) {
            return true;
        } else if (l && r) {
            return (l->val == r->val) &&
                isSymmetric(l->left, r->right) &&
                isSymmetric(l->right, r->left);
        } else {
            return false;
        }
    }
public:
    static bool isSymmetric(const TreeNode* root) {
        return isSymmetric(root->left, root->right);
    }
};
