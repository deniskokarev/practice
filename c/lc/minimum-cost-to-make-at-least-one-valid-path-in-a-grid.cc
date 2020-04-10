class Solution {
	using E = struct { int to, cost; };
	using G = vector<vector<E>>;
	using Q = pair<int,int>;
	static int node(int i, int j, int h, int w) {
		if (i<0)
			i = 0;
		else if (i >= h)
			i = h-1;
		if (j<0)
			j = 0;
		else if (j >= w)
			j = w-1;
		return i*w+j;
	}
public:
	static int minCost(const vector<vector<int>> &grid) {
		int h = grid.size();
		int w = grid[0].size();
		G gg(h*w);
		for (int i=0; i<h; i++) {
			for (int j=0; j<w; j++) {
				switch(grid[i][j]) {
				case 1:
					gg[node(i,j,h,w)].push_back(E{node(i,j+1,h,w), 0});
					break;
				case 2:
					gg[node(i,j,h,w)].push_back(E{node(i,j-1,h,w), 0});
					break;
				case 3:
					gg[node(i,j,h,w)].push_back(E{node(i+1,j,h,w), 0});
					break;
				case 4:
					gg[node(i,j,h,w)].push_back(E{node(i-1,j,h,w), 0});
					break;
				}
			}
		}
		for (int i=0; i<h; i++) {
			for (int j=0; j<w; j++) {
				gg[node(i,j,h,w)].push_back(E{node(i,j+1,h,w), 1});
				gg[node(i,j,h,w)].push_back(E{node(i+1,j,h,w), 1});
				gg[node(i,j,h,w)].push_back(E{node(i,j-1,h,w), 1});
				gg[node(i,j,h,w)].push_back(E{node(i-1,j,h,w), 1});
			}
		}
		vector<int> dist(h*w, -1);
		priority_queue<Q,vector<Q>,greater<Q>> qq;
		qq.push({0,0});
		while (!qq.empty()) {
			auto p = qq.top();
			qq.pop();
			if (dist[p.second] == -1) {
				dist[p.second] = p.first;
				for (auto &e:gg[p.second])
					qq.push({p.first+e.cost,e.to});
			}
		}
		return dist[h*w-1];
	}
};

