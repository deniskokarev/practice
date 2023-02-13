//https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/
class Solution {
    static inline bool is_odd(int n) {
        return n&1;
    }
public:
    int countOdds(int low, int high) {
        return (high+1)/2 - low/2;
        // ^^^^ from below analysis
        if (is_odd(high)) {
            if (is_odd(low)) {
                // odd-odd 1,1
                return (high+1)/2 - low/2;
            } else {
                // even-odd 0,1
                return (high+1)/2 - low/2;
            }
        } else {
            if (is_odd(low)) {
                // odd-even 1,2
                return (high+1)/2 - low/2;
            } else {
                // even-even 2,2 2,3,4
                return (high+1)/2 - low/2; // either high+1 or not
            }
        }
    }
};
