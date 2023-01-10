// https://leetcode.com/problems/same-tree/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        bool ans = p && q && p->val == q->val && 
            !(p->left == nullptr ^ q->left == nullptr) &&
            !(p->right == nullptr ^ q->right == nullptr);
        return ans && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
