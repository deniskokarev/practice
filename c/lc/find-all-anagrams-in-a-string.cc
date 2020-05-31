// https://leetcode.com/problems/find-all-anagrams-in-a-string/
class Solution {
public:
    vector<int> findAnagrams(const string &s, const string &a) {
        vector<int> res;
        vector<int> ahist(256);
        int sz = a.size();
        for (unsigned char c:a)
            ahist[c]++;
        int i=0;
        int absdiff = 0;
        for (int v:ahist)
            absdiff += (v>0);
        for (i=0; i<sz; i++) {
            unsigned char c=s[i];
            absdiff += (ahist[c]==0);
            ahist[c]--;
            absdiff -= (ahist[c]==0);
        }
        if (!absdiff)
            res.push_back(i-sz);
        for (; i<s.size(); i++) {
            unsigned char c1=s[i-sz];
            absdiff += (ahist[c1]==0);
            ahist[c1]++;
            absdiff -= (ahist[c1]==0);
            unsigned char c2=s[i];
            absdiff += (ahist[c2]==0);
            ahist[c2]--;
            absdiff -= (ahist[c2]==0);
            if (!absdiff)
                res.push_back(i-sz+1);
        }
        return res;
    }
};
