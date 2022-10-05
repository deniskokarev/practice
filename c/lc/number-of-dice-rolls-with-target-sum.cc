// https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/
// CPU O(log(n)*target^2 + k)
// Mem O(log(n)*target)

constexpr int MOD = 1e9 + 7;

class Solution {
public:
    static int numRollsToTarget(int n, int k, int target) {
        // dp[p][target] is number of ways to get target with 2^p dices
        int log2n = 5;  // we know that n < 2^5
        vector<vector<int>> dp(log2n, vector<int>(target + 1));
        for (int i = 1; i <= k && i <= target; i++)
            dp[0][i] = 1;
        for (int p = 1; p < log2n; p++)
            for (int t = 2; t <= target; t++)
                for (int l = 1; l < t; l++)
                    dp[p][t] = (dp[p][t] + int64_t(dp[p - 1][l]) * dp[p - 1][t - l]) % MOD;
        // compose the answer for n from dp[][] pow2 pieces
        // as if we spliced n into several pow2 piles of dice
        // ans[prev][target] is the number of ways to get target for piles we considered so far
        int p; // current bit of n
        for (p = 0; !(n & 1); p++)
            n >>= 1;
        int i = 0; // number of piles (1-bits in n)
        vector<int> ans = dp[p];
        n >>= 1;
        p++;
        while (n > 0) {
            if (n & 1) {
                // add dp[p] pile to all prior piles of dice
                // iterating t backwards to reuse ans[]
                for (int t = target; t > 1; t--) {
                    ans[t] = 0;
                    for (int l = 1; l < t; l++)
                        ans[t] = (ans[t] + int64_t(ans[l]) * dp[p][t - l]) % MOD;
                }
            }
            n >>= 1;
            p++;
        }
        return ans[target];
    }
};

