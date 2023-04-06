class Solution {
    // 1-water, 0-land
    struct P {
        int x, y;
    };

    // paint with checking the offboard
    static void dfs_paint(vector<vector<int>> &dd, int i, int j) {
        int h = dd.size();
        int w = dd[0].size();
        if (i >= 0 && i < h && j >= 0 && j < w && !dd[i][j]) {
            dd[i][j] = -1;
            for (auto d: (const P[]) {{+1, 0},
                                      {0,  +1},
                                      {-1, 0},
                                      {0,  -1}}) {
                dfs_paint(dd, i + d.y, j + d.x);
            }
        }
    }
    // quicker painting when we cannot step offboard
    static void dfs_paint_q(vector<vector<int>> &dd, int i, int j) {
        if (!dd[i][j]) {
            dd[i][j] = -1;
            for (auto d: (const P[]) {{+1, 0},
                                      {0,  +1},
                                      {-1, 0},
                                      {0,  -1}}) {
                dfs_paint_q(dd, i + d.y, j + d.x);
            }
        }
    }
public:
    static int closedIsland(vector<vector<int>> &dd) {
        int h = dd.size();
        int w = dd[0].size();
        for (int i=0; i<h; i++) {
            dfs_paint(dd, i, 0);
            dfs_paint(dd, i, w-1);
        }
        for (int j=0; j<w; j++) {
            dfs_paint(dd, 0, j);
            dfs_paint(dd, h-1, j);
        }
        int ans = 0;
        for (int i = 1; i < h-1; i++) {
            for (int j = 1; j < w-1; j++) {
                if (!dd[i][j]) {
                    ans++;
                    dfs_paint_q(dd, i, j);
                }
            }
        }
        return ans;
    }
};
