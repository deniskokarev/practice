class BSTIterator {
    stack<TreeNode *> stack;
public:
    BSTIterator(TreeNode* root):stack() {
        while (root) {
            stack.push(root);
            root = root->left;
        }
    }
    
    int next() {
        TreeNode *root = stack.top();
        int v = root->val;
        stack.pop();
        root = root->right;
        while (root) {
            stack.push(root);
            root = root->left;
        }
        return v;
    }
    
    bool hasNext() {
        return !stack.empty();
    }
};

