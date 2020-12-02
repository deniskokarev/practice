class Solution {
public:
    bool canPartition(const vector<int>& nums) {
        int sm = accumulate(nums.begin(), nums.end(), 0);
        if (sm&1) {
            return false;
        } else {
            int half = sm/2;
            vector<uint8_t> vv(half+1, 0);
            vv[0] = 1;
            for (int n:nums)
                for (int i=half-n; i>=0; i--)
                    vv[i+n] |= vv[i];
            return vv[half];
        }
    }
};
