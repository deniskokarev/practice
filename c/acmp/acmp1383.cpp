/* ACMP 1383 */
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

struct Q {
	int len;
	int node;
	bool operator<(const Q &b) const {
		return len > b.len;
	}
};

struct E {
	int len;
	int to;
};

constexpr int DINF = 2009000999;

int main(int argc, char **argv) {
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	vector<vector<E>> ee(n);
	while (m--) {
		int i, j, w;
		scanf("%d%d%d", &i, &j, &w);
		ee[i].push_back(E{w,j});
		ee[j].push_back(E{w,i});
	}
	// dijkstra
	int dist[n];
	fill(dist, dist+n, DINF);
	priority_queue<Q> qq; // min heap len,node
	qq.push(Q {0, s});
	while (!qq.empty()) {
		auto top = qq.top();
		qq.pop();
		if (dist[top.node] == DINF) {
			dist[top.node] = top.len;
			for (auto &e:ee[top.node])
				qq.push(Q {top.len+e.len, e.to});
		}
	};
	for (auto &d:dist)
		printf("%d ", d);
	printf("\n");
	return 0;
}
