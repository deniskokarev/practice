/* ACMP 206 */
#include <cstdio>
#include <algorithm>

using namespace std;

struct E {
	int i, j;
	int tin;
	int tout;
};

constexpr int DINF = 2e9;

int main(int argc, char **argv) {
	int n, e, m;
	scanf("%d%d%d", &n, &e, &m);
	E ee[m*n];
	int eesz = 0;
	for (int i=0; i<m; i++) {
		int k;
		scanf("%d", &k);
		scanf("%d%d", &ee[eesz].i, &ee[eesz].tin);
		k--;
		while (k) {
			scanf("%d%d", &ee[eesz].j, &ee[eesz].tout);
			k--; eesz++;
			ee[eesz].i = ee[eesz-1].j;
			ee[eesz].tin = ee[eesz-1].tout;
		}
	}
	// ford to find best path
	int dd[n+1];
	fill(dd, dd+n+1, DINF);
	dd[1] = 0;
	for (int v=0; v<n-1; v++) {
		for (int ei=0; ei<eesz; ei++) {
			auto &e = ee[ei];
			if (e.tin >= dd[e.i] && dd[e.j] > e.tout)
				dd[e.j] = e.tout;
		}
	}
	printf("%d\n", dd[e]);
	return 0;
}
