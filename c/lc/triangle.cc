// https://leetcode.com/problems/triangle/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& tri) {
        int h = tri.size();
        for (int r = h-2; r >= 0; r--)
            for (int c = r; c >= 0; c--)
                tri[r][c] += min(tri[r+1][c], tri[r+1][c+1]);
        return tri[0][0];
    }
};
