// https://leetcode.com/problems/n-th-tribonacci-number/
constexpr int SZ = 3;

class Solution {
public:
    int tribonacci(int n) {
        unsigned tt[SZ] = {0, 1, 1};
        unsigned sm = 2;
        int i = 2;
        while (i < n) {
            i++;
            int p = i % SZ;
            int nv = sm;
            sm -= tt[p];
            sm += nv;
            tt[p] = nv;
        }
        return tt[n%SZ];
    }
};
