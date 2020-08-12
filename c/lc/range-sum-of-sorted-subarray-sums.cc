class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        constexpr int MX = 1e5;
        constexpr int MOD = 1e9+7;
        int sz = nums.size();
        vector<int> tot(MX+1);
        for (int i=0; i<sz; i++) {
            int sm = 0;
            for (int j=i; j<sz; j++) {
                sm += nums[j];
                tot[sm]++;
            }
        }
        vector<int> flat(sz*(sz+1)/2);
        int o = 0;
        for (int i=0; i<=MX; i++)
            for (int j=0; j<tot[i]; j++)
                flat[o++] = i;
        int sm = 0;
        for (int i=left-1; i<right; i++)
            sm = (sm + flat[i]) % MOD;
        return sm;
    }
};
