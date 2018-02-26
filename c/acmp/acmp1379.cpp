/* ACMP 1379 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int64_t DINF = INT64_MAX/2;

struct E {
	int i, j;
	int64_t w;
};

int main(int argc, char **argv) {
	int n, m, k, s, f;
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &f);
	E ee[m+n];
	for (int ei=0; ei<m; ei++) {
		auto &e = ee[ei];
		scanf("%d%d%lld", &e.i, &e.j, &e.w);
	}
	for (int i=1,ei=m; ei<m+n; i++,ei++)
		ee[ei] = {i, i, 0};
	// ford in explicit step-by-step fashion
	int64_t dd[2][n+1];
	fill(dd[0], dd[0]+n+1, DINF);
	fill(dd[1], dd[1]+n+1, DINF);
	int prev = 0;
	int cur = 1;
	dd[prev][s] = 0;
	while (k--) {
		for (const auto &e:ee)
			if (dd[cur][e.j] > dd[prev][e.i]+e.w)
				dd[cur][e.j] = dd[prev][e.i]+e.w;
		swap(cur, prev);
	}
	printf("%lld\n", (dd[prev][f]==DINF)?-1:dd[prev][f]);
	return 0;
}
