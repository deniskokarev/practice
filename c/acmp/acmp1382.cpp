/* ACMP 1382 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Q {
	int len;
	int node;
	bool operator<(const Q &b) const {
		return len > b.len; // for min heap
	}
};

struct E {
	int to;
	int weight;
	int len;
};

constexpr int DINF = -1;

inline int dijkstra(const vector<vector<E>> &ee, int n, int mxw) {
	vector<int> dist(n, DINF);
	priority_queue<Q> qq;
	qq.push(Q{0,0});
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (dist[top.node] == DINF) {
			dist[top.node] = top.len;
			for (auto &e:ee[top.node])
				if (e.weight >= mxw)
					qq.push(Q {top.len+e.len, e.to});
		}
	}
	return (dist[n-1]>1440)?DINF:dist[n-1];
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	vector<vector<E>> ee(n);
	while (m--) {
		int i;
		E e;
		cin >> i >> e.to >> e.len >> e.weight;
		i--, e.to--;
		ee[i].push_back(e);
		swap(i, e.to);
		ee[i].push_back(e);
	}
	int f = 0, t = INT_MAX;
	//fprintf(stderr, "dijkstra(0)=%d\n", dijkstra(ee, n, 0));
	while (f<t) {
		m = f+(t-f)/2;
		if (dijkstra(ee, n, m) == DINF)
			t = m;
		else
			f = m+1;
	}
	int ans = f-3*1000*1000;
	ans = (ans<0)?0:ans/100;
	printf("%d\n", ans);
	return 0;
}
