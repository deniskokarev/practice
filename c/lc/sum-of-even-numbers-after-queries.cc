// https://leetcode.com/problems/sum-of-even-numbers-after-queries/
class Solution {
    inline int even(int n) {
        return (n & 1) == 0;
    }
public:
    vector<int> sumEvenAfterQueries(vector<int>& nn, const vector<vector<int>>& qq) {
        vector<int> ans(qq.size());
        int sm = 0;
        for (auto n:nn)
            sm += n * even(n);
        int o = 0;
        for (auto &q:qq) {
            int v = q[0];
            int i = q[1];
            sm -= nn[i] * even(nn[i]);
            nn[i] += v;
            sm += nn[i] * even(nn[i]);
            ans[o++] = sm;
        }
        return ans;
    }
};
