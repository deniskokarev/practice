#include <cstdio>
#include <cstring>
#include <cinttypes>
/* CodeForces CF1139C problem */
using namespace std;

/*
 * disjoint set ops
 */

int dsu_root(int a, int *parent) {
	return (a == parent[a]) ? a : parent[a] = dsu_root(parent[a], parent);
}

void dsu_join(int a, int b, int *parent) {
	parent[dsu_root(b, parent)] = dsu_root(a, parent);
}

constexpr int MOD = 1e9+7;

unsigned pow_mod(unsigned b, unsigned p) {
        uint64_t r = 1;
        uint64_t b2 = b;
        while (p) {
                if (p&1) {
                        r *= b2;
                        r %= MOD;
                }
                b2 *= b2;
                b2 %= MOD;
                p >>= 1;
        }
        return unsigned(r);
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	int parent[n+1];
	memset(parent, 0, sizeof(parent));
	for (int i=0; i<n-1; i++) {
		int u, v, x;
		scanf("%d%d%d", &u, &v, &x);
		if (!x) {
			if (!parent[u])
				parent[u] = u;
			if (!parent[v])
				parent[v] = v;
			dsu_join(u, v, parent);
		}
	}
	int sz[n+1]; // disjoin set sizes
	memset(sz, 0, sizeof(sz));
	for (int i=1; i<=n; i++)
		sz[dsu_root(i, parent)]++;
#if 0
	for (int i=1; i<=n; i++)
		fprintf(stderr, "%d = %d\n", i, sz[i]);
#endif
	unsigned ans = pow_mod(n, k);
	ans += MOD - n;
	ans %= MOD;
	for (int i=1; i<=n; i++) {
		if (sz[i] > 0) {
			unsigned minus = pow_mod(sz[i], k);
			minus += MOD - sz[i];  // we've already excluded 1ngls
			minus %= MOD;
			ans += MOD - minus;
			ans %= MOD;
		}
	}
	printf("%u\n", ans);
	return 0;
}
