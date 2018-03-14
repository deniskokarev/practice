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
	int n, d, v;
	scanf("%d%d%d", &n, &d, &v);
	d--, v--;
	int r;
	scanf("%d", &r);
	int en[n];
	fill(en, en+n, 0);
	E ee[n][r];
	while (r--) {
		int f, tf, t, tt;
		scanf("%d%d%d%d", &f, &tf, &t, &tt);
		f--, t--;
		ee[f][en[f]++] = {tf, tt, t};
	}
	// dijkstra
	int dist[n];
	fill(dist, dist+n, DINF);
	priority_queue<Q> qq; // min heap len,node
	qq.push(Q {0, d});
	while (!qq.empty()) {
		auto top = qq.top();
		qq.pop();
		if (dist[top.node] == DINF) {
			dist[top.node] = top.time;
			for (int i=0; i<en[top.node]; i++) {
				auto &e = ee[top.node][i];
				if (e.time_src >= top.time)
					qq.push(Q {e.time_dst, e.to});
			}
		}
	};
	printf("%d\n", dist[v]);
	return 0;
}
