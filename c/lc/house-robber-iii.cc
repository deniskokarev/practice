class Solution {
    struct R {
        int take, pass, mx;    
    };
    R rob_r(const TreeNode* root) {
        if (root) {
            R l = rob_r(root->left);
            R r = rob_r(root->right);
            int take = root->val + l.pass + r.pass;
            int pass = l.mx + r.mx;
            int mx = max(take, pass);
            return R {take, pass, mx};
        } else {
            return {0,0,0};
        }
    }
public:
    int rob(TreeNode* root) {
        return rob_r(root).mx;
    }
};
