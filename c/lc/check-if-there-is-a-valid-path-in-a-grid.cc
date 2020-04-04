class Solution {
	enum {R=0, U, L, D};
	using C = array<int,4>;
	struct P {
		int i,j;
	};
public:
    static bool hasValidPath(const vector<vector<int>>& grid) {
		int h = grid.size();
		int w = grid[0].size();
		vector<vector<C>> dir(h+2, vector<C>(w+2));
		for (int i=0; i<h; i++) {
			for (int j=0; j<w; j++) {
				switch(grid[i][j]) {
				case 1:
					dir[i+1][j+1] = C {{1, 0, 1, 0}};
					break;
				case 2:
					dir[i+1][j+1] = C {{0, 1, 0, 1}};
					break;
				case 3:
					dir[i+1][j+1] = C {{0, 0, 1, 1}};
					break;
				case 4:
					dir[i+1][j+1] = C {{1, 0, 0, 1}};
					break;
				case 5:
					dir[i+1][j+1] = C {{0, 1, 1, 0}};
					break;
				case 6:
					dir[i+1][j+1] = C {{1, 1, 0, 0}};
					break;
				}
			}
		}
		vector<vector<vector<P>>> gg(h+2, vector<vector<P>>(w+2, vector<P>()));
		for (int i=0; i<h; i++) {
			for (int j=0; j<w; j++) {
				switch(grid[i][j]) {
				case 1:
					if (dir[i+1][j][R])
						gg[i+1][j+1].push_back({i+1, j});
					if (dir[i+1][j+2][L])
						gg[i+1][j+1].push_back({i+1, j+2});
					break;
				case 2:
					if (dir[i][j+1][D])
						gg[i+1][j+1].push_back({i, j+1});
					if (dir[i+2][j+1][U])
						gg[i+1][j+1].push_back({i+2, j+1});
					break;
				case 3:
					if (dir[i+1][j][R])
						gg[i+1][j+1].push_back({i+1, j});
					if (dir[i+2][j+1][U])
						gg[i+1][j+1].push_back({i+2, j+1});
					break;
				case 4:
					if (dir[i+1][j+2][L])
						gg[i+1][j+1].push_back({i+1, j+2});
					if (dir[i+2][j+1][U])
						gg[i+1][j+1].push_back({i+2, j+1});
					break;
				case 5:
					if (dir[i+1][j][R])
						gg[i+1][j+1].push_back({i+1, j});
					if (dir[i][j+1][D])
						gg[i+1][j+1].push_back({i, j+1});
					break;
				case 6:
					if (dir[i+1][j+2][L])
						gg[i+1][j+1].push_back({i+1, j+2});
					if (dir[i][j+1][D])
						gg[i+1][j+1].push_back({i, j+1});
					break;
				}
			}
		}
		vector<vector<int>> dist(h+2, vector<int>(w+2, 0));
		dist[1][1] = 1;
		deque<P> qq;
		qq.push_back({1,1});
		while(!qq.empty()) {
			auto me = qq.front();
			qq.pop_front();
			for (auto p:gg[me.i][me.j]) {
				if (!dist[p.i][p.j]) {
					dist[p.i][p.j] = dist[me.i][me.j]+1;
					qq.push_back(p);
				}
			}
		}
		return dist[h][w];
    }
};

