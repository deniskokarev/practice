/* ACMP 134 */
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Q {
	int time;
	int node;
	bool operator<(const Q &b) const {
		return time > b.time;
	}
};

struct E {
	int time_src;
	int time_dst;
	int to;
};

constexpr int DINF = -1;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int gg[n];
	for (auto &g:gg)
		scanf("%d", &g);
	int m;
	scanf("%d", &m);
	vector<vector<E>> ee(n);
	while (m--) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		ee[i].push_back(E{gg[i],j});
		ee[j].push_back(E{gg[j],i});
	}
	// dijkstra
	int dist[n];
	fill(dist, dist+n, DINF);
	priority_queue<Q> qq; // min heap len,node
	qq.push(Q {0, 0});
	while (!qq.empty()) {
		auto top = qq.top();
		qq.pop();
		if (dist[top.node] == DINF) {
			dist[top.node] = top.len;
			for (auto &e:ee[top.node])
				qq.push(Q {top.len+e.len, e.to});
		}
	};
	printf("%d\n", dist[n-1]);
	return 0;
}
