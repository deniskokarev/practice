// https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int> &aa) {
        int sz = aa.size();
        sort(begin(aa), end(aa));
        aa[0] = 1;
        for (int i=1; i<sz; i++) {
            aa[i] = min(aa[i], aa[i-1]+1);
        }
        return aa[sz-1];
    }
};
