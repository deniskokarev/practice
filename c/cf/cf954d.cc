#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cassert>
/* CodeForces CF954D problem */

using namespace std;

struct Q {
	int dist;
	int to;
	bool operator<(const Q &b) const {
		return dist > b.dist; // maxheap
	}
};

struct E {
	int to;
	E *next;
};

void dijkstra(E **ee, int *dist, int n, int s) {
	fill(dist, dist+n, -1);
	priority_queue<Q> qq;
	qq.push(Q{0,s});
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (dist[top.to]<0) {
			dist[top.to] = top.dist;
			for (int i=0; i<n; i++)
				for (E *e=ee[top.to];e;e=e->next)
					qq.push(Q{top.dist+1, e->to});
		}
	}
}

int main(int argc, char **argv) {
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	s--, t--;
	E eeall[m*2], *e = eeall;
	E *ee[n];
	fill(ee, ee+n, nullptr);
	char mm[n][n];
	memset(mm, 0, sizeof(mm));
	while (m--) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		*e = E {j, ee[i]};
		ee[i] = e++;
		*e = E {i, ee[j]};
		ee[j] = e++;
		mm[i][j] = mm[j][i] = 1;
	}
	int dist_s[n];
	dijkstra(ee, dist_s, n, s);
	int spath = dist_s[t];
	int dist_t[n];
	dijkstra(ee, dist_t, n, t);
	assert(dist_t[s] == spath);
	int ans = 0;
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			if (mm[i][j]==0 && dist_s[i]+dist_t[j]+1 >= spath && dist_s[j]+dist_t[i]+1 >= spath)
				ans++;
	printf("%d\n", ans);
	return 0;
}
