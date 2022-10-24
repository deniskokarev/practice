// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

constexpr int ASZ = 26;
using uint = unsigned;

class Solution {
public:
    static int maxLength(const vector<string> &arr) {
        int sz = arr.size();
        vector<uint> mm(sz);
        vector<int> len(sz);
        for (int i = 0; i < sz; i++) {
            bitset<ASZ> m(0);
            int l = arr[i].size();
            for (char ch: arr[i]) {
                int c = (ch - 'a') % ASZ;
                if (m[c]) {
                    l = 0; // break
                } else {
                    m[c] = 1;
                }
            }
            mm[i] = m.to_ulong();
            cerr << mm[i] << ' ';
            len[i] = l;
        }
        cerr << endl;
        int p2 = (1 << sz);
        int mx = 0;
        for (int i = 1; i < p2; i++) {
            uint msk = 0;
            int l = 0;
            bitset<ASZ> m(i);
            for (int j = 0; j < sz; j++) {
                if (m[j] && (msk & mm[j]) == 0) {
                    msk |= mm[j];
                    l += len[j];
                }
            }
            mx = max(mx, l);
        }
        return mx;
    }
};
