// https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
// O(1) space solution
class Solution {
public:
    bool arrayStringsAreEqual(const vector<string>& ww1, const vector<string>& ww2) {
        int sz1 = ww1.size();
        int sz2 = ww2.size();
        int w1 = 0, w2 = 0;
        int c1 = 0, c2 = 0;
        int wsz1 = ww1[w1].size();
        int wsz2 = ww2[w2].size();
        bool ans = true;
        int l1 = 0;
        int l2 = 0;
        while (w1 < sz1 && w2 < sz2) {
            while (c1 < wsz1 && c2 < wsz2) {
                ans &= (ww1[w1][c1++] == ww2[w2][c2++]);
                l1++, l2++;
            }
            if (c1 >= wsz1) {
                c1 = 0;
                w1++;
                if (w1 < sz1)
                    wsz1 = ww1[w1].size();
            }
            if (c2 >= wsz2) {
                c2 = 0;
                w2++;
                if (w2 < sz2)
                    wsz2 = ww2[w2].size();
            }
        }
        return ans && l1 == l2 && w1 == sz1 && w2 == sz2 && c1 == 0 && c2 == 0;
    }
};

class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        string s1, s2;
        for (auto s:word1)
            s1 += s;
        for (auto s:word2)
            s2 += s;
        return s1 == s2;
    }
};
