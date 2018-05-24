#include <cstdio>
#include <vector>
/* ACMP 557 */
using namespace std;

inline int get_el(const vector<vector<vector<int>>> &mmm, vector<vector<vector<vector<int>>>> &cache, int n, int p, int mf, int mt, int i, int j) {
	if (mf+1 == mt)
		return mmm[mf][i][j];
	if (cache[mf][mt][i][j] < 0) {
		int cc[n];
		for (int ci=0; ci<n; ci++)
			cc[ci] = get_el(mmm, cache, n, p, mf, (mf+mt)/2, i, ci);
		int rr[n];
		for (int ri=0; ri<n; ri++)
			rr[ri] = get_el(mmm, cache, n, p, (mf+mt)/2, mt, ri, j);
		int rc = 0;
		for (int i=0; i<n; i++)
			rc += cc[i]*rr[i] % p;
		cache[mf][mt][i][j] = rc%p;
	}
	return cache[mf][mt][i][j];
}

int main(int argc, char **argv) {
	int m, n;
	scanf("%d%d", &m, &n);
	int a, b;
	scanf("%d%d", &a, &b);
	int p;
	scanf("%d", &p);
	vector<vector<vector<int>>> mmm(m, vector<vector<int>>(n, vector<int>(n)));
	for (int l=0; l<m; l++)
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				scanf("%d", &mmm[l][i][j]);
	vector<vector<vector<vector<int>>>> cache(m+1, vector<vector<vector<int>>>(m+1, vector<vector<int>>(n, vector<int>(n, -1))));
	int ans = get_el(mmm, cache, n, p, 0, m, a-1, b-1);
	printf("%d\n", ans);
	return 0;
}
