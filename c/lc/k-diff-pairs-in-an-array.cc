class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int,int> prev;
        int ans = 0;
        if (k != 0) {
            sort(nums.begin(), nums.end());
            auto e = unique(nums.begin(), nums.end());
            nums.resize(e-nums.begin());
            for (int n:nums) {
                ans += prev[n+k];
                ans += prev[n-k];
                prev[n]++;
            }
        } else {
            for (int n:nums)
                prev[n]++;
            for (auto &nc:prev)
                ans += (nc.second > 1);
        }
        return ans;
    }
};
