// https://leetcode.com/problems/sort-vowels-in-a-string
class Solution {
    static inline bool isv(char c) {
        switch (c) {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }

public:
    static string &sortVowels(string &s) {
        int cnt[256]{};
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i]]++;
        }
        int p = 0;
        const string vv {"AEIOUaeiou"};
        for (auto &c:s) {
            if (isv(c)) {
                while (!cnt[vv[p]]) {
                    p++;
                }
                c = vv[p];
                cnt[vv[p]]--;
            }
        }
        return s;
    }
};

