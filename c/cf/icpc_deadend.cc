#include <cstdio>
#include <vector>
#include <list>
/* ICPC https://judge.icpc.global/problems/deadend */
using namespace std;

struct E {
	int f, t;
};

struct G {
	vector<vector<int>> nn;
	vector<E> ee;
	G(int n, int m):nn(n),ee(m+m) {
	}
};

// condense graph loops
int dfs(G &g, vector<int> &seen, int root) {
	if (!seen[root]) {
		seen[root] = 1;
		int loop = -1;
		for (int ei:g.nn[root]) {
			if (ei >= 0)
				loop = dfs(g, seen, g.ee[ei].t);
			if (loop >= 0)
				break;
		}
		if (loop >= 0) {
			vector<int> add;
			for (int &ei:g.nn[root]) {
				g.ee[ei].f = loop;
				g.ee[ei^1].t = loop;
				add.push_back(ei);
				ei = -1;
			}
			g.nn[loop].insert(g.nn[loop].end(), add.begin(), add.end());
		}
		if (loop == root)
			return -1;
		return loop;
	} else {
		return root;
	}
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	G g(n, m);
	for (int i=0; i<m; i++) {
		int v, w;
		scanf("%d%d", &v, &w);
		v--, w--;
		g.ee[2*i] = E {v, w};
		g.ee[2*i+1] = E {w, v};
		g.nn[v].push_back(2*i);
		g.nn[w].push_back(2*i+1);
	}
	vector<int> seen(n);
	dfs(g, seen, 0);
#if 1
	for (int i=0; i<n; i++) {
		fprintf(stderr, "n=%d->[", i);
		for (int ei:g.nn[i]) {
			if (ei >= 0)
				fprintf(stderr, "%d ", g.ee[ei].t);
		}
		fprintf(stderr, "]\n");
	}
#endif
	return 0;
}
