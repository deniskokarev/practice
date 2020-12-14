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
