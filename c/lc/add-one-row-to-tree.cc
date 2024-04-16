// https://leetcode.com/problems/add-one-row-to-tree/
class Solution {
    static TreeNode* addOneRow(TreeNode* root, int val, int depth, int curr_depth) {
        if (root) {
            if (curr_depth == depth) {
                root->left = new TreeNode(val, root->left, nullptr);
                root->right = new TreeNode(val, nullptr, root->right);
            } else {
                root->left = addOneRow(root->left, val, depth, curr_depth+1);
                root->right = addOneRow(root->right, val, depth, curr_depth+1);
            }
        }
        return root;
    }
public:
    static TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        TreeNode n(0, root, nullptr);
        auto a = addOneRow(&n, val, depth, 1);
        return a->left;
    }
};

enum {L, R};

class Solution {
    TreeNode* dfs(TreeNode* root, int val, int dep, int dir) {
        if (dep == 1) {
            if (dir == L)
                return new TreeNode(val, addOneRow(root, val, dep-1), nullptr);
            else
                return new TreeNode(val, nullptr, addOneRow(root, val, dep-1));
        } else if (root) {
            root->left = dfs(root->left, val, dep-1, L);
            root->right = dfs(root->right, val, dep-1, R);
        }
        return root;
    }
public:
    TreeNode* addOneRow(TreeNode* root, int val, int dep) {
        return dfs(root, val, dep, L);
    }
};
