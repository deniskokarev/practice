/* ACMP 1384 */
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
 
using namespace std;
 
struct Q {
	int node;
	unsigned c;
	int from;
	bool operator<(const Q &b) const {
		return c > b.c; // for min heap
	}
};
 
struct E {
	int to;
	unsigned c;
};
 
struct D {
	int from;
	int to;
	unsigned c;
	unsigned cto;
};
 
void minpath(const vector<vector<E>> &ee, vector<D> &dist, int start, const vector<int> &tt) {
	priority_queue<Q> qq;
	for (auto &d:dist) {
		d.c = UINT_MAX;
		d.from = -1;
	}
	qq.push(Q{start, 0, -1});
	int fnd_type = tt[start]%2+1; // 1<->2
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (tt[top.node] == fnd_type) {
			// short-circuit everything on the way
			for (int f=top.from; f>=0; f=dist[f].from) {
				if (dist[f].cto > top.c - dist[f].c) {
					dist[f].cto = top.c - dist[f].c;
					dist[f].to = top.node;
				}
			}
			return;
		} else {
			if (dist[top.node].c == UINT_MAX) {
				dist[top.node].c = top.c;
				dist[top.node].from = top.from;
				if (dist[top.node].cto == UINT_MAX) {
					for (auto &e:ee[top.node])
						qq.push(Q{e.to, top.c+e.c, top.node});
				} else {
					qq.push(Q{dist[top.node].to, top.c+dist[top.node].cto, top.node});
				}
			}
		}
	}
}
 
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> tt(n);
	for (auto &t:tt)
		scanf("%d", &t);
	vector<vector<E>> ee(n);
	while (m--) {
		int f;
		E e;
		scanf("%d%d%d", &f, &e.to, &e.c);
		f--, e.to--;
		ee[f].push_back(e);
		swap(f, e.to);
		ee[f].push_back(e);
	}
	vector<D> dist(tt.size(), D{-1,-1,UINT_MAX,UINT_MAX});
	for (int i=0; i<n; i++) {
		if (tt[i] == 1) {
			minpath(ee, dist, i, tt);
#if 0
			fprintf(stderr, "=== working on %d ===\n", i);
			for (int i=0; i<n; i++)
				fprintf(stderr, "i=%d, cto=%d, to=%d\n", i, dist[i].cto, dist[i].to);
#endif
		}
	}
	unsigned mn = UINT_MAX;
	int mni, mnj;
	for (int i=0; i<n; i++) {
		if (tt[i] == 1 && dist[i].cto < mn) {
			mn = dist[i].cto;
			mni = i;
			mnj = dist[i].to;
		}
	}
	if (mn == UINT_MAX)
		printf("-1\n");
	else
		printf("%d %d %u\n", mni+1, mnj+1, mn);
	return 0;
}
