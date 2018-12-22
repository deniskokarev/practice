#include <cstdio>
#include <cinttypes>
#include <vector>
#include <array>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/lazy-white-falcon */
using namespace std;

//#define DEBUG

struct G {
	static constexpr int L2SZ = 20; // no more 2^20 nodes
	int sz;
	vector<vector<int>> ee;
	vector<int> as_dfs; // orig node num -> dfs order num, where root=0
	vector<array<int,L2SZ>> parent; // dfs parents 1,2,4,8,... levels up
	vector<pair<int,int>> chld; // dfs node -> range of chld dfs nodes
	vector<int> lvl;			// dfs node depth
	G(int sz):sz(sz),ee(sz),as_dfs(sz),parent(sz),chld(sz),lvl(sz){};
};

void renumber_as_dfs_r(G &g, int root, int parent, int *seq, int lvl) {
	int ct = *seq;
	for (int v:g.ee[root])
		if (v != parent)
			renumber_as_dfs_r(g, v, root, seq, lvl+1);
	int cf = *seq;
	g.as_dfs[root] = cf;
	g.chld[cf] = make_pair(cf, ct);
	g.lvl[cf] = lvl;
	(*seq)--;
}

void set_parent_r(G &g, int root, int parent, int dfs_parent) {
	int dfs_root = g.as_dfs[root];
	g.parent[dfs_root][0] = dfs_parent;
	for (int pi=1; pi<G::L2SZ; pi++)
		if (g.parent[dfs_root][pi-1] >= 0)
			g.parent[dfs_root][pi] = g.parent[g.parent[dfs_root][pi-1]][pi-1];
		else
			g.parent[dfs_root][pi] = -1;
	for (int v:g.ee[root])
		if (v != parent)
			set_parent_r(g, v, root, g.as_dfs[root]);
}

void renumber_as_dfs(G &g) {
	int seq = g.sz-1;
	renumber_as_dfs_r(g, 0, -1, &seq, 0);
	set_parent_r(g, 0, -1, -1);
}

int accend(const G &g, int root, int up) {
	for (int b=G::L2SZ-1; b>=0; b--)
		if (up & (1<<b))
			root = g.parent[root][b];
	return root;
}

int lca(const G &g, int a, int b) {
	if (g.lvl[a] > g.lvl[b])
		a = accend(g, a, g.lvl[a] - g.lvl[b]);
	else
		b = accend(g, b, g.lvl[b] - g.lvl[a]);
	int f=0, t=g.lvl[a]+1;
	while (f<t) {
		int m = f+(t-f)/2;
		if (accend(g, a, m) != accend(g, b, m))
			f = m+1;
		else
			t = m;
	}
	return accend(g, a, f);
}

void fw_inc(int64_t *fw, int fw_sz, int x, int64_t d) {
	for (int i=x; i<fw_sz; i|=i+1)
		fw[i] += d;;
}

int64_t fw_sum(const int64_t *fw, int x) {
	int64_t s = 0;
	for (int i=x; i>=0; i=(i&(i+1))-1)
		s += fw[i];
	return s;
}

void do_inc(const G &g, int64_t *fw, int root, int d) {
	int dfs_root = g.as_dfs[root];
	fw_inc(fw, g.sz+1, g.chld[dfs_root].first, d);
	fw_inc(fw, g.sz+1, g.chld[dfs_root].second+1, -d);
}

int64_t do_query(const G &g, int64_t *fw, int a, int b) {
	a = g.as_dfs[a];
	b = g.as_dfs[b];
	int p = lca(g, a, b);
	int pp = g.parent[p][0];
#ifdef DEBUG
	fprintf(stderr, "lca(%d,%d) = %d\n", a, b, p);
#endif
	int64_t ans = fw_sum(fw, a) + fw_sum(fw, b) - fw_sum(fw, p);
	if (pp >= 0)
		ans -= fw_sum(fw, pp);
	return ans;
}

int main(int argc, char **argv) {
	int n, q;
	scanf("%d%d", &n, &q);
	G g(n);
	for (int i=0; i<n-1; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		g.ee[f].push_back(t);
		g.ee[t].push_back(f);
	}
	renumber_as_dfs(g);
#ifdef DEBUG
	for (int i=0; i<g.sz; i++)
		fprintf(stderr, "%d -> %d\n", i, g.as_dfs[i]);
	for (int i=0; i<g.sz; i++)
		fprintf(stderr, "%d: parent(%d), parent2(%d), chld(%d:%d), lvl(%d)\n", i, g.parent[i][0], g.parent[i][2], g.chld[i].first, g.chld[i].second, g.lvl[i]);
#endif
	int64_t fw[n+1];
	fill(fw, fw+n+1, 0);
	int64_t hist[n];
	fill(hist, hist+n, 0);
	while (q--) {
		int q, u, x;
		scanf("%d%d%d", &q, &u, &x);
		switch(q) {
		case 1:
			do_inc(g, fw, u, x-hist[u]);
			hist[u] = x;
			break;
		default:
			printf("%" PRId64 "\n", do_query(g, fw, u, x));
		}
	}
	return 0;
}
