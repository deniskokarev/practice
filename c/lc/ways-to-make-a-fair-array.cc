class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int sz = nums.size();
        nums.push_back(0);
        vector<int> odd(sz+1);
        vector<int> even(sz+1);
        even[0] = nums[0];
        for (int i=sz-1; i>=0; i--) {
            if (i&1) {
                odd[i] = odd[i+1]+nums[i];
                even[i] = even[i+1];
            } else {
                odd[i] = odd[i+1];
                even[i] = even[i+1]+nums[i];
            }
        }
        int o=0, e=0;
        int ans = 0;
        for (int i=0; i<sz; i++) {
            if (i&1) {
                ans += (e+odd[i+1] == o+even[i]);
                o += nums[i];
            } else {
                ans += (e+odd[i] == o+even[i+1]);
                e += nums[i];
            }
        }
        return ans;
    }
};
