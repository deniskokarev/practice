// https://leetcode.com/problems/toeplitz-matrix/
class Solution {
public:
    bool isToeplitzMatrix(const vector<vector<int>>& mm) {
        int h = mm.size();
        int w = mm[0].size();
        bool ans = true;
        for (int r=0; r<h-1; r++)
            for (int c=0; c<w-1; c++)
                ans &= mm[r][c] == mm[r+1][c+1];
        return ans;
    }
};
