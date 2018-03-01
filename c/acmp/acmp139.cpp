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
	} dd[n+1];
	fill(dd, dd+n+1, D {0, false});
	dd[1] = D {0, true};
	for (int v=0; v<n-1; v++) {
		for (const auto &e:ee) {
			int64_t nd = min(dd[e.i].w+e.w, DINF);
			if (dd[e.j].conn && dd[e.i].conn) {
				if (dd[e.j].w < nd)
					dd[e.j] = D {nd, true};
			} else if (dd[e.i].conn) {
				dd[e.j] = D {nd, true};
			}
		}
	}
	D ans = dd[n];
	for (const auto &e:ee) {
		int64_t nd = min(dd[e.i].w+e.w, DINF);
		if (dd[e.j].conn && dd[e.i].conn) {
			if (dd[e.j].w < nd)
				dd[e.j] = D {nd, true};
		} else if (dd[e.i].conn) {
			dd[e.j] = D {nd, true};
		}
	}
	if (ans.conn) {
		if (ans.w == DINF || ans.w < dd[n].w)
			printf(":)\n");
		else
			printf("%lld\n", ans.w);
	} else {
		printf(":(\n");
	}
	return 0;
}
