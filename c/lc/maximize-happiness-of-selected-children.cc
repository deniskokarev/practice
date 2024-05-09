// https://leetcode.com/problems/maximize-happiness-of-selected-children
class Solution {
public:
    static long long maximumHappinessSum(vector<int> &hh, int k) {
        uint64_t sm = 0;
        sort(begin(hh), end(hh), std::greater<int>());
        for (int i = 0; i < k && hh[i] > i; i++) {
            sm += hh[i] - i;
        }
        return sm;
    }
};
