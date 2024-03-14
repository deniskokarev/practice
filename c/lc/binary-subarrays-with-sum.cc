// https://leetcode.com/problems/binary-subarrays-with-sum
class Solution {
public:
    static int numSubarraysWithSum(const vector<int> &nn, int tgt) {
        int sz = nn.size();
        vector<int> hh(sz + 1);
        hh[0] = 1;
        int sm = 0;
        int ans = 0;
        for (int n: nn) {
            sm += n;
            if (sm - tgt >= 0) {
                ans += hh[sm - tgt];
            }
            hh[sm]++;
        }
        return ans;
    }
};
