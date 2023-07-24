// https://leetcode.com/problems/powx-n/
class Solution {
public:
    static inline double myPow(double x, int n) {
        double ans = 1;
        double p = x;
        int sg = (n > 0) - (n < 0);
        for (n = abs(n); n; n /= 2) {
            if (n&1)
                ans *= p;
            p *= p;
        }
        return (sg >= 0) ? ans : 1/ans;
    }
};
