// https://leetcode.com/problems/excel-sheet-column-title/
class Solution {
public:
    static string convertToTitle(int n) {
        string s;
        while (n) {
            n--;
            s += 'A' + n % 26;
            n /= 26;
        }
        reverse(begin(s), end(s));
        return s;
    }
};
