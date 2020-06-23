// https://leetcode.com/problems/dungeon-game/
class Solution {
    int best_score(const vector<vector<int>>& map, int start, int h, int w) {
        vector<vector<int>> dp(map);
        dp[0][0] += start;
        for (int j=1; j<w; j++)
            if (dp[0][j-1] > 0)
                dp[0][j] += dp[0][j-1];
            else
                dp[0][j] = -1;
        for (int i=1; i<h; i++) {
            if (dp[i-1][0] > 0)
                dp[i][0] += dp[i-1][0];
            else
                dp[i][0] = -1;
            for (int j=1; j<w; j++)
                if (dp[i-1][j] > 0 && dp[i][j-1] > 0)
                    dp[i][j] += max(dp[i-1][j], dp[i][j-1]);
                else if (dp[i-1][j] > 0)
                    dp[i][j] += dp[i-1][j];
                else if (dp[i][j-1] > 0)
                    dp[i][j] += dp[i][j-1];
                else
                    dp[i][j] = -1;
        }
        return dp[h-1][w-1];
    }
public:
    int calculateMinimumHP(const vector<vector<int>>& dungeon) {
        int h = dungeon.size();
        int w = dungeon[0].size();
        int f=1, t=INT_MAX/2;
        int ans = 0;
        while (f<=t) {
            int m = (f+t)/2;
            if (best_score(dungeon, m, h, w) > 0) {
                ans = m;
                t = m-1;
            } else {
                f = m+1;
            }
        }
        return ans;
    }
};
