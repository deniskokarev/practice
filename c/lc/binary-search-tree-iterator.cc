class BSTIterator {
    stack<const TreeNode*> stack;
    
    void push_left_leaf(const TreeNode* root) {
        while (root) {
            stack.push(root);
            root = root->left;
        }
    }
public:
    BSTIterator(const TreeNode* root):stack() {
        push_left_leaf(root);
    }
    
    int next() {
        const TreeNode* top = stack.top();
        stack.pop();
        push_left_leaf(top->right);
        return top->val;
    }
    
    bool hasNext() {
        return !stack.empty();
    }
};
