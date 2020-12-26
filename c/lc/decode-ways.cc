class Solution {
public:
    int numDecodings(string s) {
        int sz = s.size();
        vector<int64_t> dp(sz+1);
        dp[0] = 1;
        dp[1] = s[0] != '0';
        for (int i=2; i<=sz; i++) {
            dp[i] += dp[i-1] * (s[i-1] != '0');
            int d2 = stol(s.substr(i-2,2));
            dp[i] += dp[i-2] * (9 < d2 && d2 < 27);
        }
        return dp[sz];
    }
};
