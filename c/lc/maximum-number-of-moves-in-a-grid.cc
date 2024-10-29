// https://leetcode.com/problems/maximum-number-of-moves-in-a-grid
class Solution
{
    using P = struct
    {
        int r, c;
    };
    // @return max depth
    static int dfs(const vector<vector<int>>& grid, vector<vector<int>>& memo, const P& p)
    {
        int h = grid.size();
        int w = grid[0].size();
        int res = 0;
        if (memo[p.r][p.c] > -1)
        {
            return memo[p.r][p.c];
        }
        for (const P& d : (P[]){{+1, +1}, {0, +1}, {-1, +1}})
        {
            P n = {p.r + d.r, p.c + d.c};
            if (n.r >= 0 && n.r < h && n.c < w && grid[n.r][n.c] > grid[p.r][p.c])
            {
                int cres = dfs(grid, memo, n) + 1;
                res = max(res, cres);
                if (res == w - p.c)
                {
                    return memo[p.r][p.c] = res;
                }
            }
        }
        return memo[p.r][p.c] = res;
    }

public:
    static int maxMoves(const vector<vector<int>>& grid)
    {
        int h = grid.size();
        int w = grid[0].size();
        vector<vector<int>> memo(h, vector<int>(w, -1));
        int res = 0;
        for (int r = 0; r < h; r++)
        {
            res = max(res, dfs(grid, memo, {r, 0}));
        }
        return res;
    }
};


