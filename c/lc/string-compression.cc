// https://leetcode.com/problems/string-compression
class Solution {
    static inline void out(string &to, int &cnt, char c) {
        if (cnt > 1) {
            to += string(1, c) + to_string(cnt);
        } else {
            to += string(1, c);
        }
        cnt = 1;
    }
public:
    int compress(vector<char>& chars) {
        string ans;
        int sz = chars.size();
        int cnt = 1;
        for (int i=1; i<sz; i++)
            if (chars[i] != chars[i-1])
                out(ans, cnt, chars[i-1]);
            else
                cnt++;
        out(ans, cnt, chars[sz-1]);
        chars.resize(ans.size());
        copy(begin(ans), end(ans), begin(chars));
        return chars.size();
    }
};
