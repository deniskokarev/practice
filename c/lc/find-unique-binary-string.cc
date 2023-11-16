// https://leetcode.com/problems/find-unique-binary-string
class Solution {
public:
    string findDifferentBinaryString(const vector<string>& ss) {
        int sz = ss[0].size();
        int mxsz = 1<<sz;
        int msk = mxsz-1;
        vector<bool> hh(mxsz, false);
        for (auto &s:ss) {
             auto n = ::strtol(s.c_str(), nullptr, 2) & msk;
             hh[n] = true;
        }
        for (int i=0; i<mxsz; i++) {
            if (!hh[i]) {
                constexpr int MXSZ = 16;
                std::bitset<MXSZ> b(i);
                return b.to_string().substr(MXSZ - sz);
            }
        }
        return "oops";
    }
};
