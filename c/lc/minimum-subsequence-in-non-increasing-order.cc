class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int s = accumulate(nums.begin(), nums.end(), 0);
        int a = 0;
        int i = 0;
        while (2*a <= s)
            a += nums[i++];
        nums.resize(i);
        return nums;
    }
};
