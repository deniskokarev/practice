// https://leetcode.com/problems/count-good-nodes-in-binary-tree/
class Solution {
    static int goodNodes(const TreeNode *root, multiset<int> &vv) {
        if (root) {
            auto fnd = vv.upper_bound(root->val);
            int is_good = (fnd == vv.end());
            vv.insert(root->val);
            int cnt = goodNodes(root->left, vv) + goodNodes(root->right, vv) + is_good;
            vv.erase(vv.find(root->val));
            return cnt;
        } else {
            return 0;
        }
    }
public:
    static int goodNodes(const TreeNode *root) {
        multiset<int> vv;
        return goodNodes(root, vv);
    }
};

