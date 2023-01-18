// https://leetcode.com/problems/climbing-stairs/
class Solution {
public:
    int climbStairs(int n) {
        int f[2] = {0, 1};
        while (n--) {
            int nxt = f[0] + f[1];
            f[0] = f[1];
            f[1] = nxt;
        }
        return f[1];
    }
};
