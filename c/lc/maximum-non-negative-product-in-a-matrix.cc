class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        constexpr int MOD = 1e9+7;
        int h = grid.size();
        int w = grid[0].size();
        vector<vector<pair<int64_t,int64_t>>> dp(h, vector<pair<int64_t,int64_t>>(w));
        dp[0][0] = {grid[0][0], grid[0][0]};
        for (int c=1; c<w; c++) {
            dp[0][c] = {max(dp[0][c-1].first * grid[0][c], dp[0][c-1].second * grid[0][c]), min(dp[0][c-1].first * grid[0][c], dp[0][c-1].second * grid[0][c])};
        }
        for (int r=1; r<h; r++) {
            dp[r][0] = {max(dp[r-1][0].first * grid[r][0], dp[r-1][0].second * grid[r][0]), min(dp[r-1][0].first * grid[r][0], dp[r-1][0].second * grid[r][0])};
        }
        for (int r=1; r<h; r++) {
            for (int c=1; c<w; c++) {
                dp[r][c] = {max({dp[r-1][c].first * grid[r][c], dp[r-1][c].second * grid[r][c], dp[r][c-1].first * grid[r][c], dp[r][c-1].second * grid[r][c]}),
                            min({dp[r-1][c].first * grid[r][c], dp[r-1][c].second * grid[r][c], dp[r][c-1].first * grid[r][c], dp[r][c-1].second * grid[r][c]})
                           };
            }
        }
        if (dp[h-1][w-1].first < 0)
            return -1;
        else
            return dp[h-1][w-1].first%MOD;
    }
};
