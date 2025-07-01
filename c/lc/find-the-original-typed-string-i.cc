// https://leetcode.com/problems/find-the-original-typed-string-i
class Solution {
public:
    static int possibleStringCount(const string &word) {
        char p = 0;
        int ans = 1;
        int cnt = 0;
        for (auto c:word) {
            if (c != p) {
                cnt = 0;
                p = c;
            }
            ans += (cnt++ > 0);
        }
        return ans;
    }
};
