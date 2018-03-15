/* ACMP 1382 */
#include <cstdio>
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

constexpr int DINF = INT_MAX;

inline int dijkstra(const vector<vector<E>> &ee, int n, int mxw) {
	priority_queue<Q> qq;
	vector<int> dist(n, DINF);
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
	return dist[n-1];
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n , &m);
	vector<vector<E>> ee(n);
	while (m--) {
		int from ;
		E e;
		scanf("%d%d%d%d", &from, &e.to, &e.len, &e.weight);
		from--, e.to--;
		ee[from].push_back(e);
		swap(from, e.to);
		ee[from].push_back(e);
	}
	// upper bound search
	int f = 0, t = INT_MAX;
	while (f<t) {
		int m = f+(t-f)/2;
		if (dijkstra(ee, n, m) > 1440)
			t = m;
		else
			f = m+1;
	}
	f--;
	int ans = f-3*1000*1000;
	ans = (ans<0)?0:ans/100;
	printf("%d\n", min(ans,10000000)); // 10M is a tricky condition
	return 0;
}
