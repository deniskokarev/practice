// https://leetcode.com/problems/backspace-string-compare
class Solution {
    static inline string& bs(string &s) {
        auto b = begin(s), i = b;
        for (auto j = b; j != end(s); ++j) {
            if (*j == '#') {
                if (i != b) {
                    --i;
                }
            } else {
                *i++ = *j;
            }
        }
        s.resize(i - b);
        return s;
    }

public:
    static bool backspaceCompare(string &s, string &t) {
        return bs(s) == bs(t);
    }
};
