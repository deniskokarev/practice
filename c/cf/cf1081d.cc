#include <cstdio>
#include <queue>
#include <algorithm>
#include <cassert>
/* CodeForces CF1081D problem */
using namespace std;

struct E {
	int f, t, w;
	int nxt;
};

struct ECMP {
	const E *ee;
	bool operator()(int a, int b) const {
		return ee[a].w > ee[b].w;
	}
};

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	int xx[k];
	int isx[n];
	fill(isx, isx+n, 0);
	for (auto &x:xx) {
		scanf("%d", &x);
		x--;
		isx[x] = 1;
	}
	E ee[2*m+2];
	int gg[n];
	fill(gg, gg+n, -1);
	for (int i=0; i<m; i++) {
		int f, t, w;
		scanf("%d%d%d", &f, &t, &w);
		f--, t--;
		ee[2*i] = E {f, t, w, gg[f]};
		gg[f] = 2*i;
		ee[2*i+1] = E {t, f, w, gg[t]};
		gg[t] = 2*i+1;
	}
	int vv[n];
	fill(vv, vv+n, 0);
	ee[2*m] = E {-1, xx[0], 0, -1}; // need pseudo edge to start with
	priority_queue<int,vector<int>,ECMP> qq(ECMP {ee});
	qq.push(2*m);
	int bfso[n]; // including pseudo edge
	int bfso_sz = 0;
	while (!qq.empty()) {
		int e = qq.top();
		int root = ee[e].t;
		qq.pop();
		if (!vv[root]) {
			vv[root] = 1;
			bfso[bfso_sz++] = e;
			for (int e=gg[root]; e!=-1; e=ee[e].nxt)
				qq.push(e);
		}
	}
	assert(bfso_sz == n);
	for (int i=n-1; i>0; i--)
		isx[ee[bfso[i]].f] |= isx[ee[bfso[i]].t];
	int mx = -1;
	for (int i=n-1; i>0; i--)
		if (isx[ee[bfso[i]].t])
			mx = max(mx, ee[bfso[i]].w);
	for (int i=0; i<k; i++)
		printf("%d ", mx);
	printf("\n");
	return 0;
}
