// https://leetcode.com/problems/sum-of-square-numbers
class Solution {
public:
    static bool judgeSquareSum(int tgt) {
        vector<unsigned> ss;
        for (unsigned n = 0; n * n <= tgt; n++) {
            ss.push_back(n * n);
        }
        int i = 0, j = ss.size() - 1;
        while (i <= j) {
            while (i <= j && ss[i] + ss[j] > tgt) {
                j--;
            }
            while (i <= j && ss[i] + ss[j] < tgt) {
                i++;
            }
            if (i <= j && ss[i] + ss[j] == tgt) {
                return true;
            }
        }
        return false;
    }
};

