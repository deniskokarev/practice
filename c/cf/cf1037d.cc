#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cstdio>
#include <cinttypes>
#include <vector>
#include <algorithm>
/* CodeForces CF1037D problem */
using namespace std;

using G = vector<vector<int>>;

void dfs_mktree(const G &g, G &tree, int root, vector<bool> &seen) {
	seen[root] = true;
	for (auto t:g[root]) {
		if (!seen[t]) {
			tree[root].push_back(t);
			dfs_mktree(g, tree, t, seen);
		}
	}
}

void bfs_tree(const G &tree, int root, vector<int> &bfs) {
	int qh = 0, qt = 0;
	bfs[qt++] = root;
	while (qh < qt) {
		int r = bfs[qh++];
		for (auto t:tree[r])
			bfs[qt++] = t;
	}
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	G g(n, vector<int>());
	for (int i=0; i<n-1; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		g[f].push_back(t);
		g[t].push_back(f);
	}
	G tree(n, vector<int>());
	vector<bool> seen(n);
	dfs_mktree(g, tree, 0, seen);
	vector<int> bb(n);
	vector<int> vord(n);
	for (int o=0; o<n; o++) {
		int &b = bb[o];
		scanf("%d", &b);
		b--;
		vord[b] = o;
	}
	for (int i=0; i<n; i++)
		sort(tree[i].begin(), tree[i].end(), [&vord](int a, int b){return (vord[a]<vord[b]);});
	vector<int> bfs(n);
	bfs_tree(tree, 0, bfs);
	bool ans = true;
	for (int i=0; i<n; i++)
		ans &= (bb[i] == bfs[i]);
	printf("%s\n", (ans?"Yes":"No"));
	return 0;
}
