class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int sz = nums.size() + 2;
        vector<int> pl(sz, 1);
        copy(nums.begin(), nums.end(), pl.begin()+1);
        vector<int> pr(pl);
        for (int i=1; i<sz; i++)
            pl[i] *= pl[i-1];
        for (int i=sz-2; i>=0; i--)
            pr[i] *= pr[i+1];
        vector<int> ans(sz);
        for (int i=1; i<sz-1; i++)
            ans[i] = pl[i-1]*pr[i+1];
        return vector<int>(ans.begin()+1, ans.end()-1);
    }
};
