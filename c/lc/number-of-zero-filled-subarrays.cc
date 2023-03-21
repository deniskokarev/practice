// https://leetcode.com/problems/number-of-zero-filled-subarrays
class Solution {
public:
    static long long zeroFilledSubarray(const vector<int>& nums) {
        long long sm = 0;
        int z = 0;
        int sz = nums.size();
        for (auto n:nums) {
            z = (z+1) * (!n);
            sm += z;
        }
        return sm;
    }
};
