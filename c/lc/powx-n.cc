// https://leetcode.com/problems/powx-n/
class Solution {
public:
    static inline double myPow(double x, int n) {
        double ans = 1;
        double p = x;
        int sg = (n > 0) - (n < 0);
        n = abs(n);
        while (n) {
            if (n&1) {
                ans *= p;
            }
            p *= p;
            n /= 2;
        }
        return (sg >= 0) ? ans : 1/ans;
    }
};
