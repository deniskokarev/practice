class Solution {
    static constexpr int MX = 5;
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n, vector<int>(MX));
        dp[0] = {1,1,1,1,1};
        for (int i=1; i<n; i++) {
            dp[i][0] = dp[i-1][0];
            for (int j=1; j<MX; j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
        int sm = accumulate(dp[n-1].begin(), dp[n-1].end(), 0);
        return sm;
    }
};
