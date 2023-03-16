// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
class Solution {
    using R = struct {
        int b, e;
    };

    static TreeNode *
    buildTree(const vector<int> &iv, const unordered_map<int,int> &ivm, const R &ir, const vector<int> &pv, const R &pr) {
        if (pr.e > pr.b) {
            int v = pv[pr.e - 1];
            TreeNode *root = new TreeNode(v);
            int m = ivm.find(v)->second;
            int cl = m - ir.b;
            root->left = buildTree(iv, ivm, {ir.b, m}, pv, {pr.b, pr.b + cl});
            root->right = buildTree(iv, ivm, {m + 1, ir.e}, pv, {pr.b + cl, pr.e - 1});
            return root;
        } else {
            return nullptr;
        }
    }

public:
    static TreeNode *buildTree(const vector<int> &inorder, const vector<int> &postorder) {
        int sz = inorder.size();
        unordered_map<int,int> ivm;
        for (int p=0; p<sz; p++)
            ivm[inorder[p]] = p;
        return buildTree(inorder, ivm, {0, sz}, postorder, {0, sz});
    }
};
