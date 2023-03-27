// https://leetcode.com/problems/minimum-path-sum/
class Solution {
public:
    static int minPathSum(vector<vector<int>>& gg) {
        int h = gg.size();
        int w = gg[0].size();
        int r = h-1;
        int c;
        for (c=w-2; c>=0; c--)
            gg[r][c] += gg[r][c+1];
        c = w-1;
        for (r=h-2; r>=0; r--)
            gg[r][c] += gg[r+1][c];
        for (r=h-2; r>=0; r--)
            for (int c=w-2; c>=0; c--)
                gg[r][c] += min(gg[r+1][c], gg[r][c+1]);
        return gg[0][0];
    }
};
