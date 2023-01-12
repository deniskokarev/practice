// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/

constexpr int ASZ = 26;

class Solution {
    using G = vector<vector<int>>;
    static void dfs(int *cnt, vector<int> &ans, const G &gg, const string &lbl, int n, int p) {
        for (auto t:gg[n]) {
            if (t != p) {
                int ccnt[ASZ]{0};
                dfs(ccnt, ans, gg, lbl, t, n);
                for (int i=0; i<ASZ; i++)
                    cnt[i] += ccnt[i];
            }
        }
        int l = ((unsigned char)lbl[n] - 'a') % ASZ;
        cnt[l]++;
        ans[n] = cnt[l];
    }
public:
    static vector<int> countSubTrees(int sz, const vector<vector<int>>& edges, const string &lbl) {
        G gg(sz);
        for (auto &e:edges) {
            gg[e[0]].push_back(e[1]);
            gg[e[1]].push_back(e[0]);
        }
        int cnt[ASZ]{0};
        vector<int> ans(sz);
        dfs(cnt, ans, gg, lbl, 0, -1);
        return ans;
    }
};
