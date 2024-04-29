// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k
class Solution {
public:
    int minOperations(vector<int>& nums, unsigned k) {
        for (unsigned n:nums) {
            k ^= n;
        }
        bitset<32> res(k);
        return res.count();
    }
};
