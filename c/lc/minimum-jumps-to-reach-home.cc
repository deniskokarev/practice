class Solution {
	enum {F,B};
	struct Q {
		int dir, to;
		int dist;
	};
public:
	static int minimumJumps(const vector<int>& forbidden, int f, int b, int x) {
		constexpr int MX = 2000;
		constexpr int INF = INT_MAX;
		// bfs to 2-kinds of nodes: F and B
		vector<vector<int>> dist(2*MX+1, vector<int>(2, INF));
		vector<bool> allowed(2*MX+1, true);
		for (auto f:forbidden)
			allowed[f] = false;
		queue<Q> qq;
		qq.push({F,0,0});
		while (!qq.empty()) {
			Q top = qq.front();
			qq.pop();
			if (top.to >= 0 && top.to <= 2*MX && allowed[top.to] && dist[top.to][top.dir] == INF) {
				dist[top.to][top.dir] = top.dist;
				if (top.dir == F)
					qq.push({B,top.to-b,top.dist+1});
				qq.push({F,top.to+f,top.dist+1});
			}
		}
		int mn = min(dist[x][F], dist[x][B]);
		if (mn != INF)
			return mn;
		else
			return -1;
	}
};

