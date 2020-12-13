class Solution {
    int dfs_mx_dep(const TreeNode* root, int dep) {
        if (root)
            return max(dfs_mx_dep(root->left, dep+1), dfs_mx_dep(root->right, dep+1));
        else
            return dep;
    }
    struct R {
        TreeNode *res;
        int dep;
    };
    R dfs_parent_mx_dep(TreeNode* root, int dep, int mx_dep) {
        if (root) {
            R l = dfs_parent_mx_dep(root->left, dep+1, mx_dep);
            R r = dfs_parent_mx_dep(root->right, dep+1, mx_dep);
            if (l.dep == mx_dep) {
                if (r.dep == mx_dep) {
                    return R {root, l.dep};
                } else {
                    return l;
                }
            } else if (r.dep == mx_dep) {
                return r;
            } else {
                return R {nullptr, max(l.dep, r.dep)};
            }
        } else {
            return R {nullptr, dep};
        }
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs_parent_mx_dep(root, 0, dfs_mx_dep(root, 0)).res;
    }
};
