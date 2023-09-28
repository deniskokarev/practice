// https://leetcode.com/problems/sort-array-by-parity/
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int i = 0, j = nums.size()-1;
        while (i < j) {
            while (i < j && !(nums[i] & 1))
                i++;
            while (i < j && nums[j] & 1)
                j--;
            swap(nums[i], nums[j]);
        }
        return nums;
    }
};
