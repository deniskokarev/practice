class Solution {
    TreeNode* bstFromPreorder(const vector<int>& po, int &pos, int mn, int mx) {
        if (pos >= po.size()) {
            return nullptr;
        } else {
            int val = po[pos];
            if (mn < val && val < mx) {
                TreeNode* root = new TreeNode(val);
                pos++;
                root->left = bstFromPreorder(po, pos, mn, val);
                root->right = bstFromPreorder(po, pos, val, mx);
                return root;
            } else {
                return nullptr;
            }
        }
    }
public:
    TreeNode* bstFromPreorder(const vector<int>& po) {
        int pos = 0;
        return bstFromPreorder(po, pos, INT_MIN, INT_MAX);
    }
};
