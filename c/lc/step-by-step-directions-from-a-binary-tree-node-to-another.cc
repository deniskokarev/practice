// https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another
class Solution {
    struct P {
        bool dir;
        const TreeNode *n;
    };
public:
    static bool bfs(vector<P> &pp, const TreeNode* root, int tgt, bool dir) {
        auto res = false;
        if (root) {
            pp.push_back({dir, root});
            if (root->val == tgt)
                res = true;
            res = res || bfs(pp, root->left, tgt, false) || bfs(pp, root->right, tgt, true);
            if (!res)
                pp.pop_back();
        }
        return res;
    }
    static string getDirections(const TreeNode* root, int start, int tgt) {
        vector<P> sp, tp;
        bfs(sp, root, start, false);
        bfs(tp, root, tgt, false);
        int pfx = 0;
        while (pfx < sp.size() && pfx < tp.size() && sp[pfx].n->val == tp[pfx].n->val) {
            pfx++;
        }
        int ds = sp.size() - pfx;
        string ans = string(ds, 'U');
        for (int i=pfx; i<tp.size(); i++) {
            ans += tp[i].dir ? "R" : "L";
        }
        return ans;
    }
};
