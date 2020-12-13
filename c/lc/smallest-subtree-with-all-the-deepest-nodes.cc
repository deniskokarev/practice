class Solution {
    struct R {
        TreeNode *res;
        int dep;
    };
    R dfs_parent_mx_dep(TreeNode* root, int dep) {
        if (root) {
            R l = dfs_parent_mx_dep(root->left, dep+1);
            R r = dfs_parent_mx_dep(root->right, dep+1);
            if (l.dep > r.dep) {
                return l;
            } else if (l.dep < r.dep) {
                return r;
            } else {
                return R {root, max(l.dep, r.dep)};
            }
        } else {
            return R {nullptr, dep};
        }
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs_parent_mx_dep(root, 0).res;
    }
};
