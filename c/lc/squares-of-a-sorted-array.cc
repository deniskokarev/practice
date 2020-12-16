class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int sz = nums.size();
        int p = 0;
        while (p < sz && nums[p] < 0)
            p++;
        vector<int> res(sz);
        int o = 0;
        int f = p, b=p-1;
        while (b >= 0 && f < sz) {
            if (nums[f] < -nums[b])
                res[o++] = nums[f++];
            else
                res[o++] = nums[b--];
        }
        while (b >= 0)
            res[o++] = nums[b--];
        while (f < sz)
            res[o++] = nums[f++];
        for (int &r:res)
            r *= r;
        return res;
    }
};
