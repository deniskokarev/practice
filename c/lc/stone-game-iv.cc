class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<int> squares;
        for (int i=1; i*i<=n; i++)
            squares.push_back(i*i);
        vector<bool> dp(n+1, false);
        dp[0] = true;
        for (int i=0; i<=n; i++) {
            bool win = true;
            for (int j=0; j<squares.size() && squares[j] <= i; j++)
                win &= (dp[i-squares[j]]);
            dp[i] = !win;
        }
        return dp[n];
    }
};
