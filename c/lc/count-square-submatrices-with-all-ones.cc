// https://leetcode.com/problems/count-square-submatrices-with-all-ones/
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int h = matrix.size();
        int w = matrix[0].size();
        vector<vector<int>> mxsq_dp(h+1, vector<int>(w+1));
        int cnt = 0;
        for (int i=1; i<=h; i++) {
            for (int j=1; j<=w; j++) {
                int sz = mxsq_dp[i][j] = matrix[i-1][j-1] * (min({mxsq_dp[i-1][j], mxsq_dp[i][j-1], mxsq_dp[i-1][j-1]}) + 1);
                cnt += sz; 
            }
        }
        return cnt;
    }
};
