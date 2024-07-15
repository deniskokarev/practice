// https://leetcode.com/problems/create-binary-tree-from-descriptions
class Solution {
    struct N {
        TreeNode *n;
        bool has_parent;
    };
public:
    static TreeNode* createBinaryTree(const vector<vector<int>>& dd) {
        array<N, int(1e5+1)> hash{};
        for (auto &d:dd) {
            if (!hash[d[0]].n)
                hash[d[0]] = {new TreeNode(d[0]), false};
            auto p = hash[d[0]].n;
            if (!hash[d[1]].n)
                hash[d[1]] = {new TreeNode(d[1]), true};
            else
                hash[d[1]].has_parent = true;
            auto c = hash[d[1]].n;
            if (d[2])
                p->left = c;
            else
                p->right = c;
        }
        for (auto &h:hash)
            if (h.n && !h.has_parent)
                return h.n;
        return nullptr;
    }
};
