class Solution {
public:
    static string stoneGameIII(const vector<int>& sv) {
        int sz = sv.size();
        vector<int> dp(sz+1, INT_MIN/2);
        dp[sz] = 0;
        for (int i=sz-1; i>=0; i--)
            for (int j=0,sm=0; j<3 && i+j<sz; sm+=sv[i+j],j++)
                dp[i] = max(dp[i], sm+sv[i+j]-dp[i+j+1]);
        // <0, ==0, >0
        return ((const string[]){"Bob", "Tie", "Alice"})[(dp[0]>0)-(dp[0]<0)+1];
    }
};

