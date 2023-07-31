// https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
class Solution {
public:
    static int minimumDeleteSum(const string &s1, const string &s2) {
        const int sz1 = s1.size();
        const int sz2 = s2.size();
        vector<vector<int>> dp(sz1 + 1, vector<int>(sz2 + 1));
        for (int i = 0; i < sz1; i++) {
            for (int j = 0; j < sz2; j++) {
                if (s1[i] == s2[j]) {
                    dp[i + 1][j + 1] = max({dp[i][j] + s1[i], dp[i][j + 1], dp[i + 1][j]});
                } else {
                    dp[i + 1][j + 1] = max({dp[i][j + 1], dp[i + 1][j]});
                }
            }
        }
        const int sm1 = accumulate(begin(s1), end(s1), 0);
        const int sm2 = accumulate(begin(s2), end(s2), 0);
        return sm1 + sm2 - 2 * dp[sz1][sz2];
    }
};

