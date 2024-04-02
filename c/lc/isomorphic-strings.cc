// https://leetcode.com/problems/isomorphic-strings
class Solution {
public:
    static bool isIsomorphic(const string &ss, const string &tt) {
        char s2t[256]{};
        char t2s[256]{};
        int sz = ss.size();
        for (int i=0; i<sz; i++) {
            char s = ss[i], t = tt[i];
            if (s2t[s] == 0 || s2t[s] == t) {
                s2t[s] = t;
            } else {
                return false;
            }
            if (t2s[t] == 0 || t2s[t] == s) {
                t2s[t] = s;
            } else {
                return false;
            }
        }
        return true;
    }
};
