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
	E ee[m];
	for (int ei=0; ei<m; ei++)
		scanf("%d%d%d", &ee[ei].i, &ee[ei].j, &ee[ei].w);
	// ford
	struct D {
		int64_t w;
		bool conn;
		int l;
	} dd[n+1];
	fill(dd, dd+n+1, D {0, false, 0});
	dd[1] = D {0, true};
	bool path[n+1];
	fill(path, path+n+1, 0);
	for (int v=0; v<n-1; v++) {
		for (const auto &e:ee) {
			int64_t nd = min(dd[e.i].w+e.w, DINF);
			if (dd[e.j].conn && dd[e.i].conn) {
				if (dd[e.j].w < nd) {
					dd[e.j] = D {nd, true, dd[e.i].l+1};
					path[e.j] = e.i;
				}
			} else if (dd[e.i].conn) {
				dd[e.j] = D {nd, true, dd[e.i].l};
				path[e.j] = e.i;
			}
		}
	}
	D savedd[n+1];
	copy(dd, dd+n+1, savedd);
	if (dd[n].conn) {
		for (const auto &e:ee) {
			int64_t nd = min(dd[e.i].w+e.w, DINF);
			if (dd[e.j].conn && dd[e.i].conn) {
				if (dd[e.j].w < nd) {
					dd[e.j] = D {nd, true, dd[e.i].l+1};
					path[e.j] = e.i;
				}
			} else if (dd[e.i].conn) {
				dd[e.j] = D {nd, true, dd[e.i].l};
				path[e.j] = e.i;
			}
		}
		bool spath[n+1];
		fill(spath, spath+n+1, false);
		spath[1] = spath[n] = true;
		for (int ni=path[n]; ni!=1; ni=path[ni])
			spath[ni] = true;
		bool loop = false;
		for (int i=1; i<n+1; i++)
			if (spath[i] && (dd[i].w == DINF || dd[i].w > savedd[i].w))
				loop = true;
		if (loop)
			printf(":)\n");
		else
			printf("%lld\n", dd[n].w);
	} else {
		printf(":(\n");
	}
	return 0;
}
