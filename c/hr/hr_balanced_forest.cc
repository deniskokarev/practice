#include <cstdio>
#include <cinttypes>
#include <climits>
#include <vector>
#include <algorithm>
#include <map>
/* Hackerrank https://www.hackerrank.com/challenges/balanced-forest/problem */
using namespace std;

struct N {
	int64_t sum;
	int64_t cost;
};

struct G {
	int64_t total;
	vector<N> vv;
	vector<vector<int>> ee;
};

int64_t calc_sum(G &g, int root, int parent) {
	g.vv[root].sum = g.vv[root].cost;
	for (auto v:g.ee[root])
		if (v != parent)
			g.vv[root].sum += calc_sum(g, v, root);
	return g.vv[root].sum;
}	

int64_t solve2(G &g, int root, int parent, int64_t res) {
	if (2*g.vv[root].sum == g.total)
		res = min(res, g.vv[root].sum);
	else
		for (auto v:g.ee[root])
			if (v != parent)
				res = min(res, solve2(g, v, root, res));
	return res;
}

inline bool even(int64_t a) {
	return !(a & 1);
}

int64_t solve3(G &g, int root, int parent, map<int64_t, int> &take, map<int64_t, int> &take_inv, int64_t res) {
	// node we select
	if (take.find(g.vv[root].sum) != take.end())
		if (3*g.vv[root].sum >= g.total)
			res = min(res, 3*g.vv[root].sum - g.total);
	if (take_inv.find(g.vv[root].sum) != take_inv.end())
		if (3*g.vv[root].sum >= g.total)
			res = min(res, 3*g.vv[root].sum - g.total);
	// node we discard
	int64_t inv = g.total - g.vv[root].sum;
	if (even(inv) && take.find(inv/2) != take.end())
		if (g.total >= 3*g.vv[root].sum)
			res = min(res, (g.total - 3*g.vv[root].sum)/2);
	// memorise the num of inv matches before going down
	take[inv]++;
	int ninv = take[inv];
	// go down
	for (auto v:g.ee[root])
		if (v != parent)
			res = min(res, solve3(g, v, root, take, take_inv, res));
	// node we partially discard keeping one of children
	if (ninv < take[inv])
		if (2*inv >= g.vv[root].sum)
			res = min(res, 2*inv - g.vv[root].sum);
	take[inv]--;
	if (take[inv] == 0)
		take.erase(inv);
	// hope to find a node exactly like this
	take[g.vv[root].sum]++;
	// hope to find node if we discard this one
	if (even(inv))
		take_inv[inv/2]++;
	return res;
}

int main(int argc, char **argv) {
	int q;
	scanf("%d", &q);
	while (q--) {
		int n;
		scanf("%d", &n);
		G g {0, vector<N>(n), vector<vector<int>>(n, vector<int>())};
		for (auto &v:g.vv)
			scanf("%" PRId64, &v.cost);
		for (int i=0; i<n-1; i++) {
			int f, t;
			scanf("%d%d", &f, &t);
			f--, t--;
			g.ee[f].push_back(t);
			g.ee[t].push_back(f);
		}
		g.total = calc_sum(g, 0, -1);
		//fprintf(stderr, "total = %" PRId64 "\n", g.total);
		map<int64_t, int> take, take_inv;
		int64_t ans = solve2(g, 0, -1, LLONG_MAX);
		ans = solve3(g, 0, -1, take, take_inv, ans);
		printf("%" PRId64 "\n", (ans < LLONG_MAX) ? ans : -1);
	}
}
