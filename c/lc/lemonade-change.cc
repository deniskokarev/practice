// https://leetcode.com/problems/lemonade-change
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int c5 = 0, c10 = 0;
        for (auto &b:bills) {
            switch (b) {
            case 5:
                c5++;
                break;
            case 10:
                if (c5 > 0) {
                    c10++;
                    c5--;
                } else {
                    return false;
                }
                break;
            case 20:
                if (c10 > 0 && c5 > 0) {
                    c10--, c5--;
                } else if (c5 > 2) {
                    c5 -= 3;
                } else {
                    return false;
                }
                break;
            }
        }    
        return true;
    }
};
