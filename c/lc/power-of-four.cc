// https://leetcode.com/problems/power-of-four/
class Solution {
    static inline bool is_p2(unsigned n) {
        return !(n & (n-1));
    }
    static inline bool is_mod3_1(unsigned n) {
        return n%3 == 1;
    }
public:
    static inline bool isPowerOfFour(unsigned n) {
        return is_p2(n) && is_mod3_1(n);
    }
};
