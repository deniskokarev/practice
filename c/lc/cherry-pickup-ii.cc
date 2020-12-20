class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int h = grid.size();
        int w = grid[0].size();
        vector<vector<int>> dp(w+2, vector<int>(w+2));; // dp[i][j] - total score if 1st on i and 2nd on j
        for (int r=h-1; r>=0; r--) {
            vector<vector<int>> ndp(w+2, vector<int>(w+2));
            for (int i=1; i<=w; i++)
                for (int j=1; j<=w; j++)
                    if (i!=j)
                        for (int pi=i-1; pi<=i+1; pi++)
                            for (int pj=j-1; pj<=j+1; pj++)
                                ndp[i][j] = max(ndp[i][j], grid[r][i-1] + grid[r][j-1] + dp[pi][pj]);
            swap(dp, ndp);
        }
        return dp[1][w];
    }
};
