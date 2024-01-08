// https://leetcode.com/problems/range-sum-of-bst/
class Solution {
    static int sm_h(TreeNode* root, int low, int high) {
        if (root) {
            int v = root->val;
            int sm = sm_l(root->left, low, high);
            if (v <= high)
                sm += sm_h(root->right, low, high); 
            if (v >= low && v <= high)
                sm += v;
            return sm;
        } else {
            return 0;
        }
    }
    static int sm_l(TreeNode* root, int low, int high) {
        if (root) {
            int v = root->val;
            int sm = sm_h(root->right, low, high);
            if (v >= low)
                sm += sm_l(root->left, low, high); 
            if (v >= low && v <= high)
                sm += v;
            return sm;
        } else {
            return 0;
        }
    }
public:
    static int rangeSumBST(TreeNode* root, int low, int high) {
        int sm = sm_l(root->left, low, high) + sm_h(root->right, low, high);
        int v = root->val;
        if (v >= low && v <= high)
            sm += v;
        return sm;
    }
};
