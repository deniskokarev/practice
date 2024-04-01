// https://leetcode.com/problems/length-of-last-word
class Solution {
public:
    static int lengthOfLastWord(const string &s) {
        int b, e = s.size() - 1;
        for (; e >= 0 && s[e] == ' '; e--);
        for (b = e; b >= 0 && s[b] != ' '; b--);
        return e - b;
    }
};
