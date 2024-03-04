// https://leetcode.com/problems/bag-of-tokens
class Solution {
public:
    static int bagOfTokensScore(vector<int>& tt, int p) {
        sort(begin(tt), end(tt));
        int b = 0, e = tt.size() - 1;
        int s = 0;
        int ans = 0;
        while (true) {
            while (b <= e && tt[b] <= p) {
                s++;
                p -= tt[b];
                b++;
                ans = max(ans, s);
            }
            if (s == 0 || b >= e) {
                break;
            }
            p += tt[e];
            e--;
            s--;
        }
        return ans;
    }
};
