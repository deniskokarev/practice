class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int h = mat.size();
        int w = mat[0].size();
        vector<vector<int>> dph(mat);
        for (int r=1; r<h; r++)
            for (int c=0; c<w; c++)
                dph[r][c] = (dph[r-1][c]+1)*dph[r][c];
        int ans = 0;
        for (int r=0; r<h; r++) {
            for (int c=0; c<w; c++) {
                ans += dph[r][c];
                int mnh = dph[r][c];
                for (int l=c-1; l>=0 && dph[r][l]>0; l--) {
                    mnh = min(mnh, dph[r][l]);
                    ans += mnh;
                }
            }
        }
        return ans;
    }
};
