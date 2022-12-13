// https://leetcode.com/problems/leaf-similar-trees/
class Solution {
    using N = const TreeNode*;

    struct Triter {
        vector<N> ss;
        Triter(N r) {
            push_left_branch(r);
        }
        bool has_next() {
            return !ss.empty();
        }
        void push_left_branch(N n) {
            while(n) {
                ss.push_back(n);
                n = n->left;
            }
        }
        N get_next() {
            N r = ss.back();
            ss.pop_back();
            push_left_branch(r->right);
            return r;
        }
    };
    static inline bool is_leaf(N n) {
        return n->left == nullptr && n->right == nullptr;
    }
    static bool probe_leafs(Triter &t) {
        while (t.has_next()) {
            N n = t.get_next();
            if (is_leaf(n)) {
                return true;
            }
        }
        return false;
    }
public:
    static bool leafSimilar(N root1, N root2) {
        Triter t1(root1), t2(root2);
        bool ans = true;
        while (t1.has_next() && t2.has_next()) {
            int v1 = -1, v2 = -1;
            while (t1.has_next()) {
                N n = t1.get_next();
                if (is_leaf(n)) {
                    v1 = n->val;
                    break;
                }
            }
            while (t2.has_next()) {
                N n = t2.get_next();
                if (is_leaf(n)) {
                    v2 = n->val;
                    break;
                }
            }
            ans &= v1 == v2;
        }
        ans &= (!probe_leafs(t1) && !probe_leafs(t2)); // they must both end
        return ans;
    }
};
