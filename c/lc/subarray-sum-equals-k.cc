class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> ss;
        ss[0] = 1;
        int sm = 0;
        int ans = 0;
        for (auto n:nums) {
            sm += n;
            ans += ss[sm-k];
            ss[sm]++;
        }
        return ans;
    }
};
