class Solution {
public:
    string generateTheString(int n) {
        string s(n, 'a');
        if (!(n&1))
            s[0] = 'b';
        return s;
    }
};
