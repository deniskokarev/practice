class Solution {
    enum { NOT_A, A };
public:
    string breakPalindrome(string pal) {
        int sz = pal.size();
        int fpos[2] {-1, -1};
        if (sz&1) {
            int mid = sz/2;
            for (int i=sz-1; i>mid; i--)
                fpos[pal[i] == 'a'] = i;
            for (int i=mid-1; i>=0; i--)
                fpos[pal[i] == 'a'] = i;
        } else {
            for (int i=sz-1; i>=0; i--)
                fpos[pal[i] == 'a'] = i;
        }
        if (fpos[NOT_A] >= 0) {
            pal[fpos[NOT_A]] = 'a';
            return pal;
        } else if (fpos[A] >= 0) {
            pal[sz-fpos[A]-1] = 'b';
            return pal;
        } else {
            return "";
        }
    }
};
