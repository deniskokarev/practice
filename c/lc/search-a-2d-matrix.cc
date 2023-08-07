// https://leetcode.com/problems/search-a-2d-matrix/
class Solution {
public:
    bool searchMatrix(const vector<vector<int>>& mm, int target) {
        int h = mm.size();
        int w = mm[0].size();
        int f = 0, t = h*w - 1;
        while (f < t) {
            int m = f + (t-f)/2;
            int r = m / w;
            int c = m % w;
            if (mm[r][c] < target) {
                f = m + 1;
            } else {
                t = m;
            }
        }
        int r = f / w;
        int c = f % w;
        return mm[r][c] == target; 
    }
};
