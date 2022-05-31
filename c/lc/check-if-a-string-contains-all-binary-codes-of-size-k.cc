// https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/

class Solution {
public:
    bool hasAllCodes(const string &s, int k) {
        int sz = s.size();
        if (k >= sz)
            return false;
        int cdsz = (1 << k);
        unsigned msk = cdsz-1;
        vector<bool> cd(cdsz, false);
        unsigned n = 0;
        int i = 0;
        while (i < k) {
            int b = (s[i] - '0') & 1;
            n <<= 1;
            n &= msk;
            n |= b;
            i++;
        }
        cd[n] = true;
        while (i < sz) {
            int b = (s[i] - '0') & 1;
            n <<= 1;
            n &= msk;
            n |= b;
            cd[n] = true;
            i++;
        }
        return accumulate(cd.cbegin(), cd.cend(), true, std::logical_and());
    }
};
