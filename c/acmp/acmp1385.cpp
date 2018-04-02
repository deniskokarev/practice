/* ACMP 1385 */
#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Q {
	int len;
	int from, to;
	bool operator<(const Q &b) const {
		return len > b.len;
	}
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int ee[n][n+1];
	for (int i=0; i<n; i++)
		ee[i][n] = 0;
	while (m--) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		ee[i][ee[i][n]++] = j;
		ee[j][ee[j][n]++] = i;
	}
	int from[n];
	fill(from, from+n, INT_MAX);
	priority_queue<Q> qq;
	qq.push(Q{1,-1,0});
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (from[top.to] == INT_MAX) {
			from[top.to] = top.from;
			int *e = ee[top.to];
			for (int i=0; i<ee[top.to][n]; i++,e++)
				qq.push(Q{1, top.to, *e});
		}
	}
#if 0
	for (int i=0; i<n; i++)
		fprintf(stderr, "%d ", from[i]);
	fprintf(stderr, "\n");
#endif
	bool seen[n];
	fill(seen, seen+n, false);
	for (int i=n-1; i>=0; i--) {
		if (!seen[i]) {
			int pv=i;
			seen[pv] = true;
			int v;
			for (v=from[pv]; v>=0 && !seen[v]; pv=v,v=from[v]) {
				printf("%d %d\n", v+1, pv+1);
				seen[v] = true;
			}
			if (v >= 0)
				printf("%d %d\n", v+1, pv+1);
		}
	}
	return 0;
}
