// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor
class Solution {
    struct Rng {
        int mn, mx;
        Rng(int v): mn{v}, mx{v} {
        }
        Rng(const Rng &o, int v): mn{o.mn}, mx{o.mx} {
            mn = min(mn, v);
            mx = max(mx, v);
        }
        int dist(int v) const {
            return max(abs(mn - v), abs(mx - v));
        }
    };
    int diff(TreeNode* root, const Rng &rng) {
        if (root) {
            int self = rng.dist(root->val);
            const Rng nrng(rng, root->val);
            int left = diff(root->left, nrng);
            int right = diff(root->right, nrng);
            return max({self, left, right});
        } else {
            return 0;
        }
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        const Rng rng(root->val);
        return diff(root, rng);
    }
};
