// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
class Solution {
    static int in_order(const TreeNode *root, int &k) {
        if (root) {
            int l = in_order(root->left, k);
            if (!k)
                return l;
            k--;
            if (!k)
                return root->val;
            return in_order(root->right, k);
        }
        return 0;
    }
public:
    static int kthSmallest(const TreeNode* root, int k) {
        return in_order(root, k); 
    }
};
