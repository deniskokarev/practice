// https://leetcode.com/problems/find-the-difference/
class Solution {
public:
    char findTheDifference(string s, string t) {
        int sm1 = accumulate(begin(s), end(s), 0);
        int sm2 = accumulate(begin(t), end(t), 0);
        return sm2 - sm1;
    }
};
