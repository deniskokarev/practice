// https://leetcode.com/problems/number-of-operations-to-make-network-connected/
class Solution {
    using G = vector<vector<int>>;

    static void dfs_paint(const G &gg, vector<int> &seen, int col, int rt) {
        if (!seen[rt]) {
            seen[rt] = col;
            for (int c: gg[rt]) {
                dfs_paint(gg, seen, col, c);
            }
        }
    }
public:
    static int makeConnected(int n, const vector<vector<int>> &conn) {
        vector<int> seen(n, 0);
        G gg(n);
        for (auto &c: conn) {
            gg[c[0]].push_back(c[1]);
            gg[c[1]].push_back(c[0]);
        }
        int col = 1;
        for (int i = 0; i < n; i++) {
            if (!seen[i]) {
                dfs_paint(gg, seen, col++, i);
            }
        }
        int con_comp = col - 1;
        int minimal_to_keep_disconn = n - con_comp;
        int need = con_comp - 1;
        return (minimal_to_keep_disconn + need <= conn.size()) ? need : -1;
    }
};

