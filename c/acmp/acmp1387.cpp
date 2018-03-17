/* ACMP 1387 == ACMP 142 */
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

struct E {
	int len;
	int to;
	E *next;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E eall[m+m];
	E *ee[n];
	fill(ee, ee+n, nullptr);
	while (m--) {
		int i, j, l;
		scanf("%d%d%d", &i, &j, &l);
		i--, j--;
		eall[m*2] = E {l, j, ee[i]};
		ee[i] = &eall[m*2];
		eall[m*2+1] = E {l, i, ee[j]};
		ee[j] = &eall[m*2+1];
	}
	int from[n];
	fill(from, from+n, INT_MAX);
	priority_queue<Q> qq;
	qq.push(Q{0,-1,0});
	int ans = 0;
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (from[top.to] == INT_MAX) {
			ans += top.len;
			from[top.to] = top.from;
			for (E *e = ee[top.to]; e; e=e->next)
				qq.push(Q{e->len, top.to, e->to});
		}
	}
	printf("%d\n", ans);
	return 0;
}
