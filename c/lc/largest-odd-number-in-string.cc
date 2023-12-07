// https://leetcode.com/problems/largest-odd-number-in-string/
class Solution {
public:
    string largestOddNumber(const string &nn) {
        int sz = nn.size();
        for (int i=sz-1; i>=0; i--)
            if ((nn[i] - '0') & 1)
                return nn.substr(0, i+1);
        return "";        
    }
};
