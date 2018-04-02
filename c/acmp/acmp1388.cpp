/* ACMP 1388 */
#include <stdio.h>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct E {
	int len;
	int to;
	int id;	// id to be used for exclusion
	E *next;
};

struct Q {
	int len;
	int to;
	int id;
	bool operator<(const Q &b) const {
		return len > b.len;
	}
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E eall[m+m];
	E *ee[n];
	fill(ee, ee+n, nullptr);
	for (int k=0; k<m; k++) {
		int i, j, l;
		scanf("%d%d%d", &i, &j, &l);
		i--, j--;
		eall[k*2] = E {l, j, k+1, ee[i]};
		ee[i] = &eall[k*2];
		eall[k*2+1] = E {l, i, k+1, ee[j]};
		ee[j] = &eall[k*2+1];
	}
	// seen[] array contains uniq ids
	int seen[n];
	fill(seen, seen+n, -1);
	// all answers are by default +INF
	int ans[m+1];
	fill(ans, ans+m+1, INT_MAX);
	// collect ids of all edges on the min spanning tree
	int ids[m];
	int ids_sz = 0;
	// regular MST run
	{
		int id = 0;
		ans[id] = 0;
		priority_queue<Q> qq;
		qq.push(Q{0,0,-1});
		while (!qq.empty()) {
			Q top = qq.top();
			qq.pop();
			if (seen[top.to] != id) {
				seen[top.to] = id;
				ans[id] += top.len;
				ids[ids_sz++] = top.id;
				for (E *e = ee[top.to]; e; e=e->next)
					qq.push(Q{e->len, e->to, e->id});
			}
		}
	}
	// subsequent MST runs excluding only one edge laying on original MST
	for (int i=1; i<ids_sz; i++) {
		int id = ids[i];
		ans[id] = 0;
		priority_queue<Q> qq;
		qq.push(Q{0,0});
		int cnt = 0;
		while (!qq.empty()) {
			Q top = qq.top();
			qq.pop();
			if (seen[top.to] != id) {
				seen[top.to] = id;
				ans[id] += top.len;
				cnt++;
				for (E *e = ee[top.to]; e; e=e->next)
					if (e->id != id)
						qq.push(Q{e->len, e->to});
			}
		}
		if (cnt != n)
			ans[id] = INT_MAX;
	}
	sort(ans, ans+m+1);
	printf("%d %d\n", ans[0], ans[1]);
	return 0;
}
