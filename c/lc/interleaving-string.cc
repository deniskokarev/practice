// https://leetcode.com/problems/interleaving-string/
class Solution {
public:
    static bool isInterleave(const string &s1, const string &s2, const string &s3) {
        int sz1 = s1.size();
        int sz2 = s2.size();
        int sz3 = s3.size();

        if (sz1+sz2 != sz3)
            return false;

        vector<vector<bool>> dp(sz1+2, vector<bool>(sz2+2));
        dp[1][1] = true;
        for (int l=1; l<=sz3; l++) {
            int l1 = min(sz1, l);
            int l2 = min(sz2, l - l1);

            while (l1 >= 0 && l2 <= sz2) {
                dp[l1+1][l2+1] = (dp[l1+1][l2] && s2[l2-1] == s3[l-1] || dp[l1][l2+1] && s1[l1-1] == s3[l-1]);
                l1--;
                l2++;
            }
        }
        return dp[sz1+1][sz2+1];
    }
};

