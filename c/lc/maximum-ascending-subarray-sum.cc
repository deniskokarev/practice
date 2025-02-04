// https://leetcode.com/problems/maximum-ascending-subarray-sum
class Solution {
public:
    static int maxAscendingSum(const vector<int>& nn) {
        int sz = nn.size();
        int sm = nn[0];
        int mx = sm;
        for (int i=1; i<sz; i++) {
            if (nn[i-1] >= nn[i]) {
                mx = max(mx, sm);
                sm = 0;
            }
            sm += nn[i];
        }
        return max(mx, sm);
    }
};
