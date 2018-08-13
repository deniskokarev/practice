#include <iostream>
#include <cstring>
/* CodeForces CF1006E problem */
using namespace std;

struct E {
	int to;
	E *nxt;
};

struct D {
	int l, sz;
};

int dfs(E *ee[], int root, D *dd, int *vv, int from) {
	dd[root].l = from;
	vv[from] = root+1;
	int sz = 1;
	for (const E *e=ee[root];e;e=e->nxt)
		sz += dfs(ee, e->to, dd, vv, from+sz);
	dd[root].sz = sz;
	return sz;
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	int pp[n];
	pp[0] = -1;
	for (int i=1; i<n; i++) {
		cin >> pp[i];
		pp[i]--;
	}
	E allee[n-1], *ep = allee;
	memset(allee, 0, sizeof(allee));
	E *ee[n];
	memset(ee, 0, sizeof(ee));
	for (int j=n-1; j>0; j--) {
		ep->to = j;
		ep->nxt = ee[pp[j]];
		ee[pp[j]] = ep++;
	}
	D dd[n];
	int vv[n];
	dfs(ee, 0, dd, vv, 0);
#if 0
	for (int i=0; i<n; i++)
		cerr << vv[i] << ' ';
	cerr << endl;
	for (int i=0; i<n; i++)
		cerr << dd[i].l << ' ' << dd[i].sz << endl;
#endif
	while (k--) {
		int u, s;
		cin >> u >> s;
		u--, s--;
		if (s >= dd[u].sz)
			cout << -1 << '\n';
		else
			cout << vv[dd[u].l+s] << '\n';
	}
	return 0;
}
