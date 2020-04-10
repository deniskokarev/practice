class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int sz = nums.size();
        vector<int> ans(sz);
        for (int i=0; i<sz; i++) {
            for (int j=0; j<i; j++)
                ans[i] += (nums[i]>nums[j]);
            for (int j=i+1; j<sz; j++)
                ans[i] += (nums[i]>nums[j]);
        }
        return ans;
    }
};
