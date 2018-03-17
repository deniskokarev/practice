/* ACMP 1386 */
#include <stdio.h>
#include <algorithm>
#include <climits>
#include <queue>
#include <cmath>

using namespace std;

struct Q {
	int len;
	int to;
	bool operator<(const Q &b) const {
		return len > b.len;
	}
};

struct E {
	int len;
	int to;
	E *next;
};

struct P {
	int x, y;
	int len(const P &b) const {
		return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y);
	}
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	P pp[n];
	for (auto &p:pp)
		scanf("%d%d", &p.x, &p.y);
	int m;
	scanf("%d", &m);
	E eall[m+m+n*n];
	E *ee[n];
	fill(ee, ee+n, nullptr);
	for (int k=0; k<m; k++) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		eall[k*2] = E {0, j, ee[i]};
		ee[i] = &eall[k*2];
		eall[k*2+1] = E {0, i, ee[j]};
		ee[j] = &eall[k*2+1];
	}
	int idx=m+m;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			int len = pp[i].len(pp[j]);
			eall[idx] = E {len, j, ee[i]};
			ee[i] = &eall[idx++];
			eall[idx] = E {len, i, ee[j]};
			ee[j] = &eall[idx++];
		}
	}
	char seen[n];
	fill(seen, seen+n, false);
	priority_queue<Q> qq;
	qq.push(Q{0,0});
	double ans = 0;
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (!seen[top.to]) {
			ans += sqrt(top.len);
			seen[top.to] = 1;
			for (E *e = ee[top.to]; e; e=e->next)
				qq.push(Q{e->len, e->to});
		}
	}
	printf("%.05f\n", ans);
	return 0;
}
