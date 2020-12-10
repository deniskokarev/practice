class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int mn_r = 0, mx_r = n-1, mn_c = 0, mx_c = n-1;
        vector<vector<int>> res(n, vector<int>(n));
        int x = 1;
        while (mn_r < mx_r) {
            int r = mn_r;
            for (int c=mn_c; c<mx_c; c++)
                res[r][c] = x++;
            int c = mx_c;
            for (int r=mn_r; r<mx_r; r++)
                res[r][c] = x++;
            r = mx_r;
            for (int c=mx_c; c>mn_c; c--)
                res[r][c] = x++;
            c = mn_c;
            for (int r=mx_r; r>mn_r; r--)
                res[r][c] = x++;
            mn_r++, mx_r--, mn_c++, mx_c--;
        }
        if (mn_r == mx_r)
            res[mn_r][mn_c] = x;
        return res;
    }
};
