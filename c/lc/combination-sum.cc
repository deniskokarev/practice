class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& cand, int target) {
        vector<vector<vector<int>>> dp(target+1);
        dp[0] = {{}};
        for (int c:cand) {
            for (int t=0; t<target; t++) {
                if (t+c <= target) {
                    for (const vector<int> &curr:dp[t]) {
                        vector<int> tc(curr);
                        tc.push_back(c);
                        dp[t+c].push_back(move(tc));
                    }
                }
            }
        }
        return dp[target];
    }
};
