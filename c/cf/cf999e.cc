#include <stdio.h>
#include <vector>
/* CodeForces CF999E problem */
using namespace std;

struct E {
	int i, j;
	int next;
	bool del;
};

int dfs(const vector<int> &v, const vector<E> &ee, int root, vector<int> &col) {
	if (col[root] == 0) {
		col[root] = 1;
		int e = v[root];
		int cnt = 1;
		while (e) {
			if (!ee[e].del)
				cnt += dfs(v, ee, ee[e].j, col);
			e = ee[e].next;
		}
		return cnt;
	} else {
		return 0;
	}
}

int main(int argc, char **argv) {
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	s--;
	vector<E> ee(2*m+1+n);
	int nee = 1;
	vector<int> vf(n);
	vector<char> ispath(n);
	while (m--) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		ee[nee] = E {i, j, vf[i], false};
		vf[i] = nee++;
		if (i == s)
			ispath[j] = 1;
	}
	// adding more paths
	int more = 0;
	for (int j=0; j<n; j++) {
		if (!ispath[j]) {
			ispath[j] = 1;
			ee[nee] = E {s, j, vf[s], false};
			vf[s] = nee++;
			more++;
		}
	}
	int candel = 0;
	for (int i=0,e=vf[s]; e && i<more; e=ee[e].next,i++) {
		vector<int> visited(n);
		ee[e].del = true;
		int vc = dfs(vf, ee, s, visited);
		//fprintf(stderr, "removing %d->%d = %d\n", ee[e].i, ee[e].j, vc);
		if (vc == n)
			candel++;
		else
			ee[e].del = false;
	}
	printf("%d\n", more-candel);
	return 0;
}
