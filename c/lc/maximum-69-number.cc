// https://leetcode.com/problems/maximum-69-number/
class Solution {
public:
    int maximum69Number (int n) {
        string s = to_string(n);
        for (int i=0; i<s.size(); i++) {
            if (s[i] == '6') {
                s[i] = '9';
                break;
            }
        }
        return stoi(s);
    }
};
