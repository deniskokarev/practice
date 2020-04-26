class Solution {
public:
    // mem = O(|text2|)
    int longestCommonSubsequence(const string &text1, const string &text2) {
        int sz1 = text1.size();
        int sz2 = text2.size();
        vector<int> mm(sz2+2);
        for (int i=1; i<=sz1; i++)
            for (int j=1,pp=mm[0],p=mm[1]; j<=sz2; j++,pp=p,p=mm[j])
                mm[j] = max({mm[j], mm[j-1], pp+(text1[i-1] == text2[j-1])});
        return mm[sz2];
    }
};
