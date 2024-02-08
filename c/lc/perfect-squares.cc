// https://leetcode.com/problems/perfect-squares/
class Solution {
public:
    static int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int s = 1; s * s <= i; s++) {
                dp[i] = min(dp[i], dp[i - s * s] + 1);
            }
        }
        return dp[n];
    }
};


class Solution {
public:
    static int numSquares(int n) {
        vector<int> hdp(n+1, INT_MAX);
        hdp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int s = sqrt(i); s > 0; s--) {
                int p = hdp[i - s * s];
                hdp[i] = min(hdp[i], p + 1);
            }
        }
        return hdp[n];
    }
};
