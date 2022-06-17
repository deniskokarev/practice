// https://leetcode.com/problems/longest-palindromic-substring/
class Solution {
public:
    static string longestPalindrome(const string &s) {
        int sz = s.size();
        int mx = 0;
        int mxp = 0;
        // odd
        for (int c = 0; c < sz; c++) {
            int l = c, r = c;
            while (l >= 0 && r < sz && s[l] == s[r]) {
                if (mx < r - l + 1) {
                    mx = r - l + 1;
                    mxp = l;
                }
                l--, r++;
            }
        }
        // even
        for (int c = 0; c < sz; c++) {
            int l = c, r = c + 1;
            while (l >= 0 && r < sz && s[l] == s[r]) {
                if (mx < r - l + 1) {
                    mx = r - l + 1;
                    mxp = l;
                }
                l--, r++;
            }
        }
        return s.substr(mxp, mx);
    }
};

