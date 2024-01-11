// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor
class Solution {
    struct Rng {
        int mn, mx;
        Rng(int v): mn{v}, mx{v} {
        }
        Rng(const Rng &o, int v): mn{min(o.mn, v)}, mx{max(o.mx, v)} {
        }
        int mx_dist(int v) const {
            return max(abs(mn - v), abs(mx - v));
        }
    };
    int mx_diff_dfs(TreeNode* root, const Rng &rng) {
        if (root) {
            int self = rng.mx_dist(root->val);
            const Rng nrng(rng, root->val);
            int left = mx_diff_dfs(root->left, nrng);
            int right = mx_diff_dfs(root->right, nrng);
            return max({self, left, right});
        } else {
            return 0;
        }
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        const Rng rng(root->val);
        return mx_diff_dfs(root, rng);
    }
};
