// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

constexpr int INF = INT_MAX / 2;

class Solution {
public:
    static int minDifficulty(const vector<int> &jobs, int d) {
        const int sz = jobs.size();
        // mx[f][t] = max(jobs on [f,t])
        vector<vector<int>> mx(sz, vector<int>(sz));
        for (int i = 0; i < sz; i++)
            mx[i][i] = jobs[i];
        for (int l = 1; l < sz; l++)
            for (int f = 0; f + l < sz; f++)
                mx[f][f + l] = max(mx[f][f + l - 1], jobs[f + l]);
        // dp[len-1] - best solution for prefix len on day d
        vector<int> dp(jobs);
        // day 1
        for (int i = 1; i < sz; i++)
            dp[i] = max(dp[i - 1], dp[i]);
        // other days
        d--;
        int z = 0;
        while (d--) {
            // iterate from back to reuse dp[]
            for (int j = sz - 1; j > 0; j--) {
                dp[j] = INF;
                for (int i = 0; i < j; i++)
                    dp[j] = min(dp[j], dp[i] + mx[i + 1][j]);
            }
            dp[z++] = INF; // no solution on pfx
        }
        return dp[sz - 1] < INF ? dp[sz - 1] : -1;
    }
};

