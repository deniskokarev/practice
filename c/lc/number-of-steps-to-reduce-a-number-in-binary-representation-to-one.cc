class Solution {
public:
    int numSteps(string s) {
        reverse(s.begin(), s.end());
        s += '0';
        int n = 0;
        for (auto c:s)
            n += (c == '1');
        int ans = 0;
        int p = 0;
        while (!((n == 1) && s[p]=='1')) {
            if (s[p] == '0') {
                p++;
            } else {
                int i;
                for (i=p; s[i]=='1'; i++) {
                    n--;
                    s[i] = '0';
                }
                s[i] = '1';
                n++;
            }
            ans++;
        }
        return ans;
    }
};
