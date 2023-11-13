// https://leetcode.com/problems/sort-vowels-in-a-string
class Solution {
    static inline bool isv(char c) {
        switch (tolower(c)) {
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
        vector<int> pp;
        int cnt[256]{};
        for (int i = 0; i < s.size(); i++) {
            unsigned char c = s[i];
            if (isv(c)) {
                pp.push_back(i);
                cnt[c]++;
            }
        }
        int p = 0;
        for (unsigned char c: "AEIOUaeiou") {
            while (cnt[c]--) {
                s[pp[p++]] = c;
            }
        }
        return s;
    }
};

