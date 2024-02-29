// https://leetcode.com/problems/even-odd-tree

class Solution {
    // BFS
    struct E {
        const TreeNode *node;
        int lvl;
    };

    static bool correct_level(const E &b) {
        return ((b.lvl ^ b.node->val) & 1);
    }

    static bool in_order(const E &a, const E &b) {
        if (!correct_level(b)) {
            return false;
        }
        if (a.lvl == b.lvl) {
            if (a.lvl & 1) {
                return a.node->val > b.node->val;
            } else {
                return a.node->val < b.node->val;
            }
        } else {
            return false;
        }
    }

public:
    static bool isEvenOddTree(const TreeNode *root) {
        E rt{root, 0};
        if (!correct_level(rt)) {
            return false;
        }
        queue<E> qq;
        qq.push(rt);
        E prev{nullptr, -1};
        while (!qq.empty()) {
            auto cur = qq.front();
            if (prev.lvl == cur.lvl) {
                if (!in_order(prev, cur)) {
                    return false;
                }
            } else {
                if (!correct_level(cur)) {
                    return false;
                }
            }
            if (cur.node->left) {
                qq.push(E{cur.node->left, cur.lvl + 1});
            }
            if (cur.node->right) {
                qq.push(E{cur.node->right, cur.lvl + 1});
            }
            qq.pop();
            prev = cur;
        }
        return true;
    }
};


class Solution {
    bool check_dfs(const TreeNode* root, vector<int> &last, int lvl) {
        if (root) {
            if ((root->val&1) == (lvl&1))
                return false;
            if (last.size() <= lvl) {
                last.push_back(root->val);
            } else {
                if (lvl&1) {
                    if (root->val >= last[lvl])
                        return false;
                } else {
                    if (root->val <= last[lvl])
                        return false;
                }
                last[lvl] = root->val;
            }
            return check_dfs(root->left, last, lvl+1) && check_dfs(root->right, last, lvl+1);
        } else {
            return true;
        }
    }
public:
    bool isEvenOddTree(TreeNode* root) {
        vector<int> last;
        return check_dfs(root, last, 0);
    }
};

