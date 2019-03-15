#include <cstdio>
#include <vector>
#include <algorithm>
/* CodeForces CF1138C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int>> mm(n, vector<int>(m));
	vector<vector<int>> rr(n, vector<int>(m));
	vector<vector<int>> cc(m, vector<int>(n));
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			int v;
			scanf("%d", &v);
			mm[i][j] = rr[i][j] = cc[j][i] = v;
		}
	}
	for (int i=0; i<n; i++) {
		sort(rr[i].begin(), rr[i].end());
		size_t sz = unique(rr[i].begin(), rr[i].end()) - rr[i].begin();
		rr[i].resize(sz);
	}
	for (int j=0; j<m; j++) {
		sort(cc[j].begin(), cc[j].end());
		size_t sz = unique(cc[j].begin(), cc[j].end()) - cc[j].begin();
		cc[j].resize(sz);
	}
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			int v = mm[i][j];
			int prr = int(lower_bound(rr[i].begin(), rr[i].end(), v) - rr[i].begin());
			int pcc = int(lower_bound(cc[j].begin(), cc[j].end(), v) - cc[j].begin());
			int mx = int(max(rr[i].size(), cc[j].size()));
			if (prr < pcc) {
				int d = pcc-prr;
				mx = max(mx, int(rr[i].size()+d));
			} else {
				int d = prr-pcc;
				mx = max(mx, int(cc[j].size()+d));
			}
			printf("%d ", mx);
		}
		printf("\n");
	}
	return 0;
}
