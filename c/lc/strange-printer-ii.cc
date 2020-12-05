class Solution {
	struct R {
		int mn_x, mx_x;
		int mn_y, mx_y;
		int x, y; // bot right
		int h, w;
	};
public:
	static bool isPrintable(const vector<vector<int>>& grid) {
		constexpr int MXC = 60;
		int h = grid.size();
		int w = grid[0].size();
		vector<vector<vector<int>>> cc(MXC+1, vector<vector<int>>(h+1, vector<int>(w+1)));
		vector<R> rr(MXC+1, {INT_MAX/2, INT_MIN/2, INT_MAX/2, INT_MIN/2, -1, -1, -1, -1});
		for (int r=1; r<=h; r++)
			for (int c=1; c<=w; c++)
				for (int col=1; col<=MXC; col++)
					cc[col][r][c] = cc[col][r-1][c] + cc[col][r][c-1] - cc[col][r-1][c-1] + (col == grid[r-1][c-1]);
		vector<vector<int>> zgrid(h+1, vector<int>(w+1));
		for (int r=1; r<=h; r++) {
			for (int c=1; c<=w; c++) {
				int col = grid[r-1][c-1];
				rr[col].mn_x = min(rr[col].mn_x, c);
				rr[col].mn_y = min(rr[col].mn_y, r);
				rr[col].mx_x = max(rr[col].mx_x, c);
				rr[col].mx_y = max(rr[col].mx_y, r);
			}
		}
		for (int col=0; col<=MXC; col++) {
			rr[col].x = rr[col].mx_x;
			rr[col].y = rr[col].mx_y;
			rr[col].w = rr[col].mx_x - rr[col].mn_x + 1;
			rr[col].h = rr[col].mx_y - rr[col].mn_y + 1;
			//cerr << "col=" << col << " x=" << rr[col].x << " y=" << rr[col].y << endl;
		}
		for (int iter=0; iter<=MXC; iter++) {
			for (int col=1; col<=MXC; col++) {
				auto &r = rr[col];
				if (r.x > 0 && r.y > 0) {
					const auto &acnt = cc[col];
					const auto &zcnt = cc[0];
					int cnt = acnt[r.y][r.x] - acnt[r.y-r.h][r.x] - acnt[r.y][r.x-r.w] + acnt[r.y-r.h][r.x-r.w];
					int z = zcnt[r.y][r.x] - zcnt[r.y-r.h][r.x] - zcnt[r.y][r.x-r.w] + zcnt[r.y-r.h][r.x-r.w];
					if (cnt+z == r.w * r.h) {
						for (int i=r.y-r.h+1; i<=r.y; i++)
							for (int j=r.x-r.w+1; j<=r.x; j++)
								zgrid[i][j] = 1;
						for (int r=1; r<=h; r++)
							for (int c=1; c<=w; c++)
								cc[0][r][c] = cc[0][r-1][c] + cc[0][r][c-1] - cc[0][r-1][c-1] + zgrid[r][c];
						r.x = r.y = -1;
					}
				}
			}
		}
#if 0
		for (int i=0; i<=h; i++) {
			for (int j=0; j<=w; j++)
				cerr << zgrid[i][j] << ' ';
			cerr << '\n';
		}
		//cerr << cc[0][h][w] << endl;
#endif
		return cc[0][h][w] == (h*w);
	}
};

