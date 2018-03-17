/* ACMP 1388 */
#include <stdio.h>
#include <algorithm>
#include <climits>
#include <queue>

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
	int id;
	E *next;
};

struct P {
	int x, y;
	int len(const P &b) const {
		return (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y);
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
	int seen[n];
	fill(seen, seen+n, -2);
	int ans[m+1];
	fill(ans, ans+m+1, 0);
	// id - is the edge we want to exclude this iteration
	for (int id=0; id<m+1; id++) { 
		priority_queue<Q> qq;
		qq.push(Q{0,0});
		int cnt = 0;
		while (!qq.empty()) {
			Q top = qq.top();
			qq.pop();
			if (seen[top.to] != id) {
				ans[id] += top.len;
				cnt++;
				seen[top.to] = id;
				for (E *e = ee[top.to]; e; e=e->next)
					if (e->id != id)
						qq.push(Q{e->len, e->to});
			}
		}
		if (cnt != n)
			ans[id] = INT_MAX;
	}
	sort(ans, ans+m+1);
	unique(ans, ans+m+1);
	printf("%d %d\n", ans[0], ans[1]);
	return 0;
}
