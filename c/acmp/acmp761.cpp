/* ACMP 761 */
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

struct E {
	int vf;
	int vt;
	int id;
	E *next;
};

struct S {
	int vf, vt;
	E *e;
};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E allee[m*2];
	E *e = allee;
	E *ee[n];
	fill(ee, ee+n, nullptr);
	int ecnt[n];
	fill(ecnt, ecnt+n, 0);
	for (int i=0; i<m; i++) {
		int vf, vt;
		scanf("%d%d", &vf, &vt);
		vf--, vt--;
		ecnt[vf]++;
		ecnt[vt]++;
		*e = E {vf, vt, i, ee[vf]};
		ee[vf] = e++;
		*e = E {vt, vf, i, ee[vt]};
		ee[vt] = e++;
	}
	int vcolor[n];
	fill(vcolor, vcolor+n, -1);
	int color = 0;
	struct C {
		int odd, even;
		int edges;
	} ccnt[n];
	fill(ccnt, ccnt+n, C{0,0,0});
	for (int i=0; i<n; i++) {
		if (vcolor[i] < 0) {
			queue<int> qq;
			qq.push(i);
			while (!qq.empty()) {
				int v = qq.front();
				qq.pop();
				if (vcolor[v]<0) {
					vcolor[v] = color;
					if (ecnt[v]&1)
						ccnt[color].odd++;
					else
						ccnt[color].even++;
					ccnt[color].edges += ecnt[v];
					for (auto e=ee[v]; e; e=e->next)
						qq.push(e->vt);
				}
			}
			color++;
		}
	}
	int ans = 0;
	for (int c=0; c<color; c++) {
		assert((ccnt[c].odd & 1) == 0);
		if (ccnt[c].edges > 0) {
			if (ccnt[c].odd == 0) {
				ans++;
			} else {
				ans += ccnt[c].odd/2;
			}
		}
	}
	printf("%d\n", ans);
}
