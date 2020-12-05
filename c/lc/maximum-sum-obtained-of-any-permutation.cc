class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        constexpr int MOD = 1e9+7;
        int sz = nums.size();
        vector<int> cg(sz+1);
        for (auto &r:requests) {
            cg[r[0]] += 1;
            cg[r[1]+1] -= 1;
        }
        for (int i=1; i<=sz; i++)
            cg[i] += cg[i-1];
        sort(cg.begin(), cg.end(), greater<int>());
        sort(nums.begin(), nums.end(), greater<int>());
        int64_t res = 0;
        for (int i=0; i<sz; i++) {
            res += ((int64_t)cg[i]) * nums[i];
            res %= MOD;
        }
        return res;
    }
};
