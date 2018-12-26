#include <cstdio>
#include <algorithm>
/* CodeForces CF1093D problem */
using namespace std;

constexpr int MOD = 998244353;

struct E {
	int f, t;
	int dir;
	int nxt;
};

int64_t p2m(int p) {
	if (p > 0) {
		int64_t ph = p2m(p/2);
		if (p&1)
			return ph*ph*2 % MOD;
		else
			return ph*ph % MOD;
	} else {
		return 1;
	}
}

int do_paint(int n, int *vv, const int *gg, const E *ee, int root) {
	int ans = (vv[root] == 1);
	for (int e=gg[root]; e!=-1; e=ee[e].nxt) {
		if (vv[ee[e].t] == -1) {
			vv[ee[e].t] = (vv[root]^1);
			int r = do_paint(n, vv, gg, ee, ee[e].t);
			if (r >= 0)
				ans += r;
		} else if (vv[ee[e].t] == vv[root]) {
			ans = -1;
			break;
		}
	}
	return ans;
}

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		scanf("%d%d", &n, &m);
		E ee[2*m];
		int gg[n];
		fill(gg, gg+n, -1);
		for (int i=0; i<m; i++) {
			int f, t;
			scanf("%d%d", &f, &t);
			f--, t--;
			ee[2*i] = E {f, t, -1, gg[f]};
			gg[f] = 2*i;
			ee[i*2+1] = E {t, f, -1, gg[t]};
			gg[t] = 2*i+1;
		}
		int vv[n];
		fill(vv, vv+n, -1);
		vv[0] = 0;
		int r = do_paint(n, vv, gg, ee, 0);
		if (r >= 0)
			printf("%d\n", int(p2m(r)+p2m(n-r))%MOD);
		else
			printf("0\n");
	}
	return 0;
}
