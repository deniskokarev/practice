// https://leetcode.com/problems/count-good-nodes-in-binary-tree/
class Solution {
    static int goodNodes(const TreeNode *root, int mx) {
        if (root) {
            int v = root->val;
            if (v >= mx) {
                return goodNodes(root->left, v) + goodNodes(root->right, v) + 1;
            } else {
                return goodNodes(root->left, mx) + goodNodes(root->right, mx);
            }
        } else {
            return 0;
        }
    }
public:
    static int goodNodes(const TreeNode *root) {
        return goodNodes(root, INT_MIN);
    }
};
