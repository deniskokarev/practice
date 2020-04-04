class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& mm) {
        int h = mm.size();
        int w = mm[0].size();
        vector<vector<int>> sel(h, vector<int>(w));
        for (int i=0; i<h; i++) {
            int mn_idx = 0;
            for (int j=0; j<w; j++)
                if (mm[i][j] < mm[i][mn_idx])
                    mn_idx = j;
            sel[i][mn_idx] += 1;
        }
        for (int j=0; j<w; j++) {
            int mx_idx = 0;
            for (int i=0; i<h; i++)
                if (mm[i][j] > mm[mx_idx][j])
                    mx_idx = i;
            sel[mx_idx][j] += 1;
        }
        vector<int> ans;
        for (int i=0; i<h; i++)
            for (int j=0; j<w; j++)
                if (sel[i][j] > 1)
                    ans.push_back(mm[i][j]);
        return ans;
    }
};
