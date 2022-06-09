// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
class Solution {
public:
    vector<int> twoSum(const vector<int>& nums, int tgt) {
        int sz = nums.size();
        int i = 0;
        int j = sz - 1;
        while (i < j) {
            if (nums[i] + nums[j] > tgt) {
                j--;
            } else if (nums[i] + nums[j] < tgt) {
                i++;
            } else {
                return {i+1, j+1};
            }
        }
        return {0, 0};
    }
};
