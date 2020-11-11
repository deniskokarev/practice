class Solution {
public:
    int maxLengthBetweenEqualCharacters(const string &s) {
        int sz = s.size();
        int pos[26]{0};
        int mx = -1;
        for (int i=0; i<sz; i++) {
            int c = s[i]-'a';
            if (pos[c]) {
                mx = max(mx, i-pos[c]);
            } else {
                pos[c] = i+1;
            }
        }
        return mx;
    }
};
