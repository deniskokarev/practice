// https://leetcode.com/problems/majority-element
class Solution {
public:
    static int majorityElement(const vector<int>& nn) {
        int v = nn[0];
        int hit = 0;
        for (auto n:nn) {
            hit += (n == v) ? +1 : -1;
            if (!hit) {
                v = n;
                hit = 1;
            }
        }
        return v;
    }
};
