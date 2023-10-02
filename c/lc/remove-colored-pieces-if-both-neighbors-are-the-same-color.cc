// https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color
class Solution {
public:
    bool winnerOfGame(const string &s) {
        int sz = s.size();
        int la = 0, lb = 0;
        int a = 0, b = 0;
        int mode = 0;
        for (int i=0; i<sz; i++) {
            if (s[i] == 'B') {
                if (la > 2) {
                    a += la - 2;
                }
                la = 0;
                lb++;
            } else {
                if (lb > 2) {
                    b += lb - 2;
                }
                lb = 0;
                la++;
            }
        }
        if (la > 2) {
            a += la - 2;
        } else if (lb > 2) {
            b += lb - 2;
        }
        return a > b;
    }
};
