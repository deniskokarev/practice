// https://leetcode.com/problems/sign-of-the-product-of-an-array/
class Solution {
    static inline int sign(int n) {
        return (n > 0) - (n < 0);
    }
    static inline int smul(int a, int b) {
        return sign(a) * sign(b);
    }
public:
    static inline int arraySign(const vector<int>& nums) {
        return accumulate(begin(nums), end(nums), 1, smul);
    }
};
