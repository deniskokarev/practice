// https://leetcode.com/problems/find-original-array-from-doubled-array/
constexpr int MXV = 1e5;

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& cc) {
        int sz = cc.size();
        vector<int> vv(MXV+1);
        for (auto v:cc)
            vv[v]++;
        vector<int> ans;
        for (int i=0; i<= MXV/2; i++) {
            while (vv[i] > 0) {
                ans.push_back(i);
                vv[i]--;
                vv[2*i]--;
            }
        }
        bool empty = true;
        for (auto v:vv)
            empty &= !v;
        if (empty)
            return ans;
        else
            return {};
    }
};
