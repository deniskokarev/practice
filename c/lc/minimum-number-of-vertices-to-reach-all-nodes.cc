class Solution {
    struct DSU {
        vector<int> par;
        DSU(int n):par(n) {
            for (int i=0; i<n; i++)
                par[i] = i;
        }
        int parent(int n) {
            if (par[n] == n)
                return n;
            else
                return par[n] = parent(par[n]);
        }
        void join(int p, int c) {
            par[c] = parent(p);
        }
    };
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        DSU dsu(n);
        for (auto &e:edges)
            dsu.join(e[0], e[1]);
        set<int> mn;
        for (int i=0; i<n; i++)
            mn.insert(dsu.parent(i));
        return vector<int>{mn.begin(), mn.end()};
    }
};
