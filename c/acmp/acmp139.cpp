/* ACMP 139 */
#include <cstdio>
#include <algorithm>

using namespace std;

struct E {
	int i, j;
	int w;
	int cnt;
};

struct D {
	int64_t w;
	bool lead2n;
	bool conn;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E ee[m];
	fill(ee, ee+m, E {0, 0, 0, 0});
	for (int i=0; i<m; i++)
		scanf("%d%d%d", &ee[i].i, &ee[i].j, &ee[i].w);
	// ford
	D dd[n+1];
	fill(dd, dd+n+1, D {INT64_MIN/2, false, false});
	// mark all vertices that may lead to n
	dd[n] = D {INT64_MIN/2, true, false};
	for (int v=0; v<n-1; v++)
		for (int i=0; i<m; i++)
			dd[ee[i].i].lead2n |= dd[ee[i].j].lead2n;
	// ford to find best path
	dd[1].w = 0;
	dd[1].conn = true;
	bool has_loop = false;
	for (int v=0; v<n; v++) {
		for (int i=0; i<m; i++) {
			auto &e = ee[i];
			if (dd[e.i].conn && dd[e.j].conn && dd[e.j].w < dd[e.i].w+e.w) {
				dd[e.j].w = min(dd[e.i].w+e.w, INT64_MAX/2);
				if (e.cnt++)
					has_loop = dd[e.j].lead2n;
			} else if (dd[e.i].conn && !dd[e.j].conn) {
				dd[e.j].w = min(dd[e.i].w+e.w, INT64_MAX/2);
				dd[e.j].conn = true;
				e.cnt++;
			}
		}
	}
	if (has_loop) {
		printf(":)\n");
	} else if (dd[n].w == INT64_MIN/2) {
		printf(":(\n");
	} else {
		printf("%lld\n", dd[n].w);
	}
	return 0;
}
