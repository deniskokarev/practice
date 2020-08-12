class Solution {
public:
    int minDifference(vector<int>& nums) {
        int sz = nums.size();
        if (sz <= 4)
            return 0;
        sort(nums.begin(), nums.end());
        int mn = INT_MAX;
        for (int l=0,r=sz-4; l<4; l++,r++)
            mn = min(mn, nums[r] - nums[l]);
        return mn;
    }
};
