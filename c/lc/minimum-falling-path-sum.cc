// https://leetcode.com/problems/minimum-falling-path-sum
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& mat) {
        int h = mat.size();
        int w = mat[0].size();
        for (int r=1; r<h; r++) {
            vector<int> sm(w, INT_MAX);
            for (int c=0; c<w; c++) {
                for (int o=-1; o<2; o++) {
                    int nc = c+o;
                    if (nc >=0 && nc < w) {
                        sm[nc] = min(sm[nc], mat[r-1][c]+mat[r][nc]);
                    }
                }
            }
            mat[r] = sm;
        }
        return *min_element(begin(mat[h-1]), end(mat[h-1]));
    }
};
