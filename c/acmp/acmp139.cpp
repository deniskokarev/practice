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
	int from_i;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E ee[m];
	fill(ee, ee+m, E {0, 0, 0, 0});
	for (int i=0; i<m; i++)
		scanf("%d%d%d", &ee[i].i, &ee[i].j, &ee[i].w);
	// keep only biggest edges from same i->j
	sort(ee, ee+m, [](const E &a, const E &b) {return (a.i<b.i) || (a.j==b.j && a.j < b.j) || (a.i==b.i && a.j==b.j && a.w > b.w);});
	auto t = unique(ee, ee+m, [](const E &a, const E &b){return a.i==b.i && a.j==b.j;});
	m = t-ee;
	D dd[n+1];
	fill(dd, dd+n+1, D {INT64_MIN/2, 0});
	dd[1] = D {0, -1};
	bool loop[n+1];
	fill(loop, loop+n+1, false);
	for (int v=0; v<2*n; v++) {
		for (int i=0; i<m; i++) {
			auto &e = ee[i];
			if (dd[e.i].from_i && dd[e.j].w < dd[e.i].w+e.w) {
				dd[e.j].w = min(dd[e.i].w+e.w, INT64_MAX/2);
				dd[e.j].from_i = e.i;
				if (e.cnt++)
					loop[e.j] = true;
			}
		}
	}
	int i;
	bool has_loop = false;
	for (i=n; i>0 && !(has_loop=loop[i]); i=dd[i].from_i) {
		fprintf(stderr, "%d <-\n", i);
	}
	if (has_loop) {
		printf(":)\n");
	} else if (dd[n].from_i == 0) {
		printf(":(\n");
	} else {
		printf("%lld\n", dd[n].w);
	}
	return 0;
}
