// https://leetcode.com/problems/sum-of-all-subset-xor-totals
class Solution {
    static int dfs(const vector<int> &nums, int x, int p) {
        if (p < 0) {
            return x;
        } else {
            return dfs(nums, x, p - 1) + dfs(nums, x ^ nums[p], p - 1);
        }
    }

public:
    static int subsetXORSum(const vector<int> &nums) {
        return dfs(nums, 0, nums.size() - 1);
    }
};

