class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sz = nums.size();
        int lsm = 0;
        int l = 0;
        int mn = INT_MAX;
        while (l<sz) {
            lsm += nums[l++];
            if (lsm == x)
                mn = l;
        }
        if (lsm < x)
            return -1;
        // lsm is [0..sz-1]
        int r = sz;
        int rsm = 0;
        while (r > 0) {
            r--;
            rsm += nums[r];
            while (lsm + rsm > x && l > 0)
                lsm -= nums[--l];
            if (lsm + rsm == x)
                mn = min(mn, l + sz - r);
        }
        if (mn == INT_MAX)
            return -1;
        else
            return mn;
    }
};
