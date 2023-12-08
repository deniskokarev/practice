// https://leetcode.com/problems/construct-string-from-binary-tree/
class Solution {
    static void tree2str_r(string &out, const TreeNode* root) {
        if (root) {
            out += to_string(root->val);
            if (root->left || root->right) {
                out += '(';
                tree2str_r(out, root->left);
                out += ')';
                if (root->right) {
                    out += '(';
                    tree2str_r(out, root->right);
                    out += ')';
                }
            }
        }
    }
public:
    static string tree2str(const TreeNode* root) {
        string res;
        tree2str_r(res, root);
        return res;
    }
};
