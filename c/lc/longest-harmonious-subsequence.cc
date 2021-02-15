class Solution {
public:
    int findLHS(vector<int>& nums) {
        map<int,int> val2cnt;
        for (auto n:nums)
            val2cnt[n]++;
        pair<int,int> lst(-1e9-3, 0);
        int mx = 0;
        for (auto kv:val2cnt) {
            if (kv.first-lst.first == 1)
                mx = max(mx, kv.second+lst.second);
            lst = kv;
        }
        return mx;
    }
};
