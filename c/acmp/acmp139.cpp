/* ACMP 139 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int64_t DINF = INT64_MAX/2;

struct E {
	int i, j, w;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E ee[m+n];
	for (int ei=0; ei<m; ei++)
		scanf("%d%d%d", &ee[ei].i, &ee[ei].j, &ee[ei].w);
	// adding main diagonal
	for (int i=1,ei=m; ei<m+n; i++,ei++)
		ee[ei] = {i, i, 0};
	// ford
	int64_t dd[n+1];
	fill(dd, dd+n+1, -DINF);
	dd[1] = 0;
	for (int v=0; v<n-1; v++)
		for (const auto &e:ee)
			dd[e.j] = max(dd[e.j], min(dd[e.i]+e.w, DINF));
	int64_t ans = dd[n];
	for (const auto &e:ee)
		dd[e.j] = max(dd[e.j], min(dd[e.i]+e.w, DINF));
	if (ans == DINF || ans < dd[n])
		printf(":)\n");
	else if (ans == -DINF)
		printf(":(\n");
	else
		printf("%lld\n", ans);
	return 0;
}
