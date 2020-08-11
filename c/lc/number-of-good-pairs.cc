class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int sz = nums.size();
        int cnt = 0;
        for (int i=0; i<sz; i++)
            for (int j=i+1; j<sz; j++)
                cnt += (nums[i] == nums[j]);
        return cnt;
    }
};
