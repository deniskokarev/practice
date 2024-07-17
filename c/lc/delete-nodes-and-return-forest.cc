// https://leetcode.com/problems/delete-nodes-and-return-forest
class Solution {
    using A = array<bool, 1001>;
    using P = TreeNode*;

    P del(vector<P> &res, P root, const A& rm) {
        if (root) {
            root->left = del(res, root->left, rm);
            root->right = del(res, root->right, rm);
            if (rm[root->val]) {
                if (root->left) {
                    res.push_back(root->left);
                }
                if (root->right) {
                    res.push_back(root->right);
                }
                root = nullptr;
            }
        }
        return root;
    }
public:
    vector<P> delNodes(P root, const vector<int>& to_del) {
        vector<P> res;
        A rm;
        for (auto d:to_del) {
            rm[d] = true;
        }
        P r = del(res, root, rm);
        if (r) {
            res.push_back(r);
        }
        return res;
    }
};
