// https://leetcode.com/problems/same-tree/
class Solution {
public:
    static bool isSameTree(const TreeNode* p, const TreeNode* q) {
        return (
            !p && !q ||
            p && q &&
            p->val == q->val &&
            isSameTree(p->left, q->left) &&
            isSameTree(p->right, q->right)
        );
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q)
            return true;
        return p && q &&
            p->val == q->val &&
            isSameTree(p->left, q->left) &&
            isSameTree(p->right, q->right);
    }
};
