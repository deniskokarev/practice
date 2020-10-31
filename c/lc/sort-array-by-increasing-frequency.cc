class Solution {
    struct P {
        int v, f;
        bool operator<(const P &o) const {
            return f<o.f || (f==o.f && v>o.v);
        }
    };
public:
    vector<int> frequencySort(vector<int>& nums) {
        int sz = nums.size();
        vector<int> freq(201);
        for (auto n:nums)
            freq[n+100]++;
        vector<P> pp(sz);
        for (int i=0; i<sz; i++)
            pp[i] = {nums[i], freq[nums[i]+100]};
        sort(pp.begin(), pp.end());
        vector<int> res(sz);
        for (int i=0; i<sz; i++)
            res[i] = pp[i].v;
        return res;
    }
};
