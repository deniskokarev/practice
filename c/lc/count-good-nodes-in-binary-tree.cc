// https://leetcode.com/problems/count-good-nodes-in-binary-tree/
class Solution {
    static int goodNodes(const TreeNode *root, vector<int> &vv) {
        if (root) {
            int v = root->val;
            int cnt;
            if (vv.empty() || vv.back() <= v) {
                vv.push_back(v);
                cnt = goodNodes(root->left, vv) + goodNodes(root->right, vv) + 1;
                vv.pop_back();
            } else {
                cnt = goodNodes(root->left, vv) + goodNodes(root->right, vv);
            }
            return cnt;
        } else {
            return 0;
        }
    }
public:
    static int goodNodes(const TreeNode *root) {
        vector<int> vv;
        return goodNodes(root, vv);
    }
};

