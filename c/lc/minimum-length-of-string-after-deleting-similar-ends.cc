// https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/
class Solution {
public:
    static int minimumLength(const string &s) {
        int i = 0, j = s.size() - 1;
        while (i < j && s[i] == s[j]) {
            char c = s[i];
            while (i <= j && s[i] == c)
                i++;
            while (i <= j && s[j] == c)
                j--;
        }
        return j - i + 1;
    }
};
