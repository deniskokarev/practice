/* ACMP 1379 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

struct E {
	int i, j, w;
};

int main(int argc, char **argv) {
	int n, m, k, s, f;
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &f);
	E ee[m];
	for (auto &e:ee)
		scanf("%d%d%d", &e.i, &e.j, &e.w);
	// ford in explicit step-by-step fashion
	int dd[2][n+1];
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
	printf("%d\n", (dd[prev][f]==DINF)?-1:dd[prev][f]);
	return 0;
}
