// https://leetcode.com/problems/island-perimeter
class Solution {
public:
    int islandPerimeter(const vector<vector<int>>& grid) {
        int h = grid.size();
        int w = grid[0].size();
        vector<vector<int>> gg(h+2, vector<int>(w+2));
        for (int i=0; i<h; i++)
            for (int j=0; j<w; j++)
                gg[i+1][j+1] = grid[i][j];
        int p = 0;
        for (int i=1; i<h+2; i++) {
            for (int j=1; j<w+2; j++) {
                p += !gg[i-1][j] && gg[i][j];
                p += gg[i][j] && !gg[i+1][j];
                p += !gg[i][j-1] && gg[i][j];
                p += gg[i][j] && !gg[i][j+1];
            }
        }
        return p;
    }
};
