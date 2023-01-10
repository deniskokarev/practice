// https://leetcode.com/problems/binary-tree-preorder-traversal/
// using iterator
class Solution {
	using T = const TreeNode*;
    static inline void push_left(vector<int> &ans, vector<T> &stack, T n) {
        while (n) {
            ans.push_back(n->val);
            stack.push_back(n);
            n = n->left;
        }
    }
public:
    static vector<int> preorderTraversal(T root) {
        vector<int> ans;
        vector<T> stack;
        push_left(ans, stack, root);
        while (!stack.empty()) {
            T top = stack.back();
            stack.pop_back();
            push_left(ans, stack, top->right);
        }
        return ans;
    }
};
