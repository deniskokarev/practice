#include <cstdio>
#include <algorithm>
/* CodeForces CF1090D problem */
using namespace std;

struct E {
	int f, t;
	int dir;
	int nxt;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E ee[2*m];
	int gg[n];
	fill(gg, gg+n, -1);
	int vv[n];
	fill(vv, vv+n, -1);
	for (int i=0; i<m; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		ee[2*i] = E {f, t, -1, gg[f]};
		gg[f] = 2*i;
		ee[i*2+1] = E {t, f, -1, gg[t]};
		gg[t] = 2*i+1;
	}
	int seq = 0;
	for (int i=0; i<n; i++) {
		if (vv[i] == -1) {
			int qq[n];
			int h = 0, t = 0;
			qq[t++] = i;
			vv[i] = seq++;
			while (h<t) {
				int nn = qq[h++];
				for (int e=gg[nn]; e!=-1; e=ee[e].nxt) {
					if (ee[e].dir == -1) {
						if (vv[ee[e].t] == -1) {
							ee[e].dir = 0;
							ee[e^1].dir = 1;				
							vv[ee[e].t] = seq++;
							qq[t++] = ee[e].t;
						} else {
							ee[e].dir = 1;
							ee[e^1].dir = 0;				
						}
					}
				}
			}
		}
	}
	int drn = -1;
	for (int i=0; i<n-1; i++) {
		bool fwd = false;
		for (int e=gg[i]; e!=-1; e=ee[e].nxt)
			fwd |= (ee[e].dir == 0);
		if (!fwd)
			drn = i;
	}
	if (drn != -1) {
		printf("YES\n");
		for (int i=0; i<n; i++)
			printf("%d ", vv[i]+1);
		printf("\n");
		for (int i=0; i<n; i++)
			if (i == drn)
				printf("%d ", seq);
			else
				printf("%d ", vv[i]+1);
		printf("\n");
	} else {
		printf("NO\n");
	}
	return 0;
}
