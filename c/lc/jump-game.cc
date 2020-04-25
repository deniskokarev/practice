class Solution {
public:
    bool canJump(vector<int>& nums) {
        int sz = nums.size();
        vector<int> dp(sz+1);
        dp[sz-1] = 1;
        dp[sz] = 0;
        for (int i=sz-2; i>=0; i--) {
            int r = min(sz-1, i+nums[i]);
            dp[i] = dp[i+1] + (dp[i+1]-dp[r+1] > 0);
        }
        return dp[0]>dp[1];
    }
};
