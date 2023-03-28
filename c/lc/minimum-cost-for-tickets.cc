// https://leetcode.com/problems/minimum-cost-for-tickets
class Solution {
public:
    static int mincostTickets(const vector<int> &days, const vector<int> &costs) {
        int sz = days.size();
        int dsz = 365;
        int di = 0;
        int ans = 0;
        vector<int> dp(dsz + 31);
        for (int i = 30; i < dsz + 31 && di < sz; i++) {
            if (i == days[di] + 30) {
                dp[i] = min({dp[i - 1] + costs[0], dp[i - 7] + costs[1], dp[i - 30] + costs[2]});
                ans = dp[i];
                di++;
            } else {
                dp[i] = dp[i - 1];
            }
        }
        return ans;
    }
};
