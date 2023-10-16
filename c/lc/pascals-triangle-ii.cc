// https://leetcode.com/problems/pascals-triangle-ii/
class Solution {
public:
    static vector<int> getRow(int n) {
        vector<int> rr(n + 1);
        uint64_t a = 1;
        for (int k=n, i=1; k>=0; k--,i++) {
            rr[k] = a;
            a *= k;
            a /= i;
        }
        return rr;
    }
};

