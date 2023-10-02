// https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color
class Solution {
public:
    bool winnerOfGame(const string &s) {
        int la = 0, lb = 0;
        int a = 0, b = 0;
        for (char c:s) {
            if (c == 'B') {
                a += (la > 2) * (la - 2);
                la = 0;
                lb++;
            } else {
                b += (lb > 2) * (lb - 2);
                lb = 0;
                la++;
            }
        }
        a += (la > 2) * (la - 2);
        b += (lb > 2) * (lb - 2);
        return a > b;
    }
};
