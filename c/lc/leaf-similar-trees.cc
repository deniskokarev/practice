// https://leetcode.com/problems/leaf-similar-trees/
class Solution {
    class TreeIter {
        vector<TreeNode *> stack;

        void push_left(TreeNode *n) {
            while (n) {
                stack.push_back(n);
                n = n->left;
            }
        }

    public:
        TreeIter(TreeNode *r) {
            push_left(r);
        }

        TreeNode *next() {
            if (!stack.empty()) {
                auto r = stack.back();
                stack.pop_back();
                push_left(r->right);
                return r;
            } else {
                return nullptr;
            }
        }
    };

    class LeafIter : public TreeIter {
    public:
        LeafIter(TreeNode *r) : TreeIter(r) {}

        TreeNode *next() {
            auto n = TreeIter::next();
            while (n && (n->left || n->right)) {
                n = TreeIter::next();
            }
            return n;
        }
    };

public:
    static bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        LeafIter it1(root1), it2(root2);
        auto n1 = it1.next();
        auto n2 = it2.next();
        while (n1 && n2 && n1->val == n2->val) {
            n1 = it1.next();
            n2 = it2.next();
        }
        return n1 == nullptr && n2 == nullptr;
    }
};



class Solution2 {
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
public:
    static bool leafSimilar(N root1, N root2) {
        Triter t1(root1), t2(root2);
        bool ans = true;
        while (t1.has_next() || t2.has_next()) {
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
            ans &= v1 == v2; // if either ends first that becomes comparison to -1
        }
        return ans;
    }
};

