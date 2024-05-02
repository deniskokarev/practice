// https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative
class Solution {
public:
    static int findMaxK(const vector<int>& nums) {
        vector<bool> seen_pos(1001); 
        vector<bool> seen_neg(1001);
        int ans = -1;
        for (auto n:nums) {
            if (n > 0) {
                seen_pos[n] = true;
            } else {
                n = -n;
                seen_neg[n] = true;
            }
            if (seen_pos[n] && seen_neg[n]) {
                ans = max(ans, n);
            }
        }
        return ans;
    }
};
