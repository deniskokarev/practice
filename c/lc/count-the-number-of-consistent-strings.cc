// https://leetcode.com/problems/count-the-number-of-consistent-strings
class Solution {
    static constexpr int SZ = 'z' - 'a' + 1;
    static unsigned long s2b(const string &s) {
        bitset<SZ> b{};
        for (unsigned char c:s) {
            b[(c-'a') % SZ] = 1;
        }
        return b.to_ulong();
    }
public:
    static int countConsistentStrings(const string &allowed, const vector<string>& words) {
        unsigned na = ~s2b(allowed);
        int ans = 0;
        for (auto &s:words) {
            unsigned w = s2b(s);            
            ans += ((w & na) == 0);
        }
        return ans;        
    }
};

class Solution {
public:
    int countConsistentStrings(const string &allowed, const vector<string>& words) {
        int ans = 0;
        bool has[256]{0};
        for (unsigned char c:allowed)
            has[c] = true;
        for (const string &w:words) {
            bool ok = true;
            for (unsigned char c:w) {
                ok &= has[c];
            }
            ans += ok;
        }
        return ans;
    }
};
