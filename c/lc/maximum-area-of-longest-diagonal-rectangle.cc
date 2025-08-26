// https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle
class Solution {
public:
    static int areaOfMaxDiagonal(vector<vector<int>>& rr) {
        int mxa = 0;
        int mxd2 = 0;
        for (auto &r:rr) {
            int d2 = r[0]*r[0]+r[1]*r[1];
            if (d2 > mxd2) {
                mxd2 = d2;
                mxa = r[0]*r[1];
            } else if (d2 == mxd2) {
                mxa = max(mxa, r[0]*r[1]);
            }
        }
        return mxa;
    }
};
