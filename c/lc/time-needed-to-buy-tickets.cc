// https://leetcode.com/problems/time-needed-to-buy-tickets
// bruteforce :-(
class Solution {
public:
    static int timeRequiredToBuy(vector<int> &tt, int k) {
        int sz = tt.size();
        int p = 0;
        int ans = 0;
        while (tt[k] > 0) {
            if (tt[p] > 0) {
                tt[p]--;
                ans++;
            }
            p++;
            p %= sz;
        }
        return ans;
    }
};
