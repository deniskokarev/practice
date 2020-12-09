class Codec {
public:
    void serialize_impl(string &out, const TreeNode* root) {
        out += '(';
        if (root) {
            out += to_string(root->val);
            serialize_impl(out, root->left);
            serialize_impl(out, root->right);
        }
        out += ')';
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string out;
        serialize_impl(out, root);
        return out;
    }

    TreeNode* deserialize_impl(const string &data, int &pos) {
        pos++;
        if (data[pos]==')') {
            pos++;
            return nullptr;
        } else {
            int e = pos;
            const char *b = data.c_str() + pos;
            const char *ptr = b;
            int val = strtol(b, (char**)&ptr, 10);
            pos += ptr-b;
            TreeNode *root = new TreeNode(val);
            root->left = deserialize_impl(data, pos);
            root->right = deserialize_impl(data, pos);
            pos++;
            return root;
        }
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(const string &data) {
        int pos = 0;
        return deserialize_impl(data, pos);
    }
};

