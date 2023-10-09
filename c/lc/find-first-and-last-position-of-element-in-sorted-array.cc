// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int b = lower_bound(begin(nums), end(nums), target) - begin(nums);
        int e = upper_bound(begin(nums), end(nums), target) - begin(nums);
        if (b == e) {
            return {-1, -1};
        } else {
            return {b, e-1};
        }
    }
};
