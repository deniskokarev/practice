// https://leetcode.com/problems/letter-combinations-of-a-phone-number/

class Solution {
    void dfs(vector<string> &out, string &cur, int p, const string &digits) {
        static const vector<string> let = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        if (p < digits.size()) {
            for (auto c:let[digits[p]-'0']) {
                cur[p] = c;
                dfs(out, cur, p+1, digits);
            }
        } else {
            out.push_back(cur);
        }
        
    }
public:
    vector<string> letterCombinations(const string &digits) {
        int sz = digits.size();
        vector<string> out;
        if (sz) {
            string cur(sz, ' ');
            dfs(out, cur, 0, digits);
        }
        return out;
    }
};

class Solution {
    static void comb(vector<string> &res, char *s, const string &digits, int p) {
        static const vector<string> let = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        if (p == digits.size()) {
            res.push_back(s);
        } else {
            for (char c: let[digits[p] - '0']) {
                s[p] = c;
                comb(res, s, digits, p + 1);
            }
        }
    }
public:
    static vector<string> letterCombinations(const string &digits) {
        vector<string> res;
        int sz = digits.size();
        if (sz) {
            char s[sz+1];
            s[sz] = 0;
            comb(res, s, digits, 0);
        }
        return res;
    }
};

