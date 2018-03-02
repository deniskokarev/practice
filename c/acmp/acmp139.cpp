/* ACMP 139 */
#include <cstdio>
#include <algorithm>

using namespace std;

struct E {
	int i, j;
	int w;
};

struct D {
	int64_t w;
	bool to_n; // leads to n
	bool from_1;	// reachable from 1
};

constexpr int64_t DINF = INT64_MAX/2;

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E ee[m];
	fill(ee, ee+m, E {0, 0, 0});
	for (int i=0; i<m; i++)
		scanf("%d%d%d", &ee[i].i, &ee[i].j, &ee[i].w);
	// bfs to mark all vertices that may lead to n
	D dd[n+1];
	fill(dd, dd+n+1, D {0, false, false});
	dd[n] = D {0, true, false};
	for (int v=0; v<n-1; v++)
		for (auto &e:ee)
			dd[e.i].to_n |= dd[e.j].to_n;
	// ford to find best path
	dd[1].w = 0;
	dd[1].from_1 = true;
	bool has_loop = false;
	for (int v=0; v<n-1; v++) {
		for (auto &e:ee) {
			if (dd[e.i].from_1 && dd[e.j].from_1) {
				if (dd[e.j].w < dd[e.i].w+e.w)
					dd[e.j].w = min(dd[e.i].w+e.w, DINF);
			} else if (dd[e.i].from_1) {
				dd[e.j].from_1 = true;
				dd[e.j].w = min(dd[e.i].w+e.w, DINF);
			}
		}
	}
	// one more ford for loop detection
	for (auto &e:ee)
		if (dd[e.i].from_1 && dd[e.j].from_1 && dd[e.j].w < dd[e.i].w+e.w)
			has_loop |= dd[e.j].to_n;
	// ans
	if (has_loop)
		printf(":)\n");
	else if (!dd[n].from_1)
		printf(":(\n");
	else
		printf("%lld\n", dd[n].w);
	return 0;
}
