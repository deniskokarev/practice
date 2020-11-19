class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> vv(n);
        vector<vector<int>> mm(n, vector<int>(n));
        for (auto r:roads) {
            vv[r[0]]++;
            vv[r[1]]++;
            mm[r[0]][r[1]] = mm[r[1]][r[0]] = 1;
        }
        int mx = 0;
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++)
                mx = max(mx, vv[i]+vv[j]-mm[i][j]);
        return mx;
    }
};
