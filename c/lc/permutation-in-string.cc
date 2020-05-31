// https://leetcode.com/problems/permutation-in-string/
class Solution {
public:
    bool checkInclusion(const string &s1, const string &s2) {
        int sz = s1.size();
        vector<int> hist(256);
        for (unsigned char c:s1)
            hist[c]++;
        int absdiff = 0;
        for (auto h:hist)
            absdiff += (h>0);
        for (int i=0; i<min(sz,int(s2.size())); i++) {
            unsigned char c = s2[i];
            absdiff += (hist[c] == 0);
            hist[c]--;
            absdiff -= (hist[c] == 0);
        }
        if (!absdiff)
            return true;
        for (int i=sz; i<s2.size(); i++) {
            unsigned char c1 = s2[i-sz];
            absdiff += (hist[c1] == 0);
            hist[c1]++;
            absdiff -= (hist[c1] == 0);
            unsigned char c2 = s2[i];
            absdiff += (hist[c2] == 0);
            hist[c2]--;
            absdiff -= (hist[c2] == 0);
            if (!absdiff)
                return true;
        }
        return false;
    }
};
