// https://leetcode.com/problems/minimum-height-trees
class Solution {
    using GG = vector<vector<int>>;

    struct DL {
        int dep, lf;
        bool deepest;

        bool operator<(const DL &o) const {
            return dep < o.dep;
        }
    };

    static DL dpst(const GG &gg, vector<int> &path, int node, int pnode, int lvl, int mxdep) {
        DL mx = {lvl, node, lvl == mxdep};
        for (int n: gg[node]) {
            if (n != pnode) {
                mx = std::max(mx, dpst(gg, path, n, node, lvl + 1, mxdep));
            }
        }
        if (mx.deepest) {
            path[lvl] = node;
        }
        return mx;
    }

    static inline bool odd(int i) {
        return i & 1;
    }

public:
    static vector<int> findMinHeightTrees(int n, const vector<vector<int>> &edges) {
        GG gg(n);
        for (auto &e: edges) {
            gg[e[0]].push_back(e[1]);
            gg[e[1]].push_back(e[0]);
        }
        vector<int> path;
        DL dl = dpst(gg, path, 0, -1, 0, -1);
        dl = dpst(gg, path, dl.lf, -1, 0, -1);
        int sz = dl.dep + 1;
        path.resize(sz);
        dpst(gg, path, dl.lf, -1, 0, dl.dep);
        if (odd(sz)) {
            return {path[sz / 2]};
        } else {
            return {path[sz / 2], path[(sz - 1) / 2]};
        }
    }
};

