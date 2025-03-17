// https://leetcode.com/problems/divide-array-into-equal-pairs
class Solution {
public:
    static bool divideArray(const vector<int>& nums) {
        static constexpr int SZ = 500;
        int cnt[SZ+1]{};
        for (auto n:nums) {
            cnt[n]++;
        }
        auto fold_even = [&cnt](bool sm, int n) {
            return sm && !(n & 1);
        };
        return accumulate(&cnt[0], &cnt[SZ], true, fold_even);
    }
};
