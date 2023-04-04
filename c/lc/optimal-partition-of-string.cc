// https://leetcode.com/problems/optimal-partition-of-string/
class Solution {
public:
    static int partitionString(const string &s) {
        unsigned seen = 0;
        int cnt = 0;
        for (auto c:s) {
            auto b = 1U << (c - 'a');
            if (seen & b) {
                cnt++;
                seen = 0;
            }
            seen |= b;
        }
        return cnt + 1;
    }
};
