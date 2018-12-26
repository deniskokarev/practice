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

template<class F, class S> void operator+=(pair<F,S> &a, const pair<F,S> &b) {
	a.first += b.first;
	a.second += b.second;
}

pair<int,int> do_paint(int n, int *vv, const int *gg, const E *ee, int root) {
	pair<int,int> r = make_pair(1, (vv[root] == 1));
	for (int e=gg[root]; e!=-1; e=ee[e].nxt) {
		if (vv[ee[e].t] == -1) {
			vv[ee[e].t] = (vv[root]^1);
			auto cr = do_paint(n, vv, gg, ee, ee[e].t);
			if (cr.second >= 0)
				r += cr;
			else
				return make_pair(-1, -1);
		} else if (vv[ee[e].t] == vv[root]) {
			return make_pair(-1, -1);
		}
	}
	return r;
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
		int64_t ans = 1;
		for (int i=0; i<n; i++) {
			if (vv[i] == -1) {
				vv[i] = 0;
				auto r = do_paint(n, vv, gg, ee, i);
				if (r.first >= 0) {
					ans *= p2m(r.second)+p2m(r.first-r.second);
					ans %= MOD;
				} else {
					ans = 0;
					break;
				}
			}
		}
		printf("%d\n", int(ans));
	}
	return 0;
}
