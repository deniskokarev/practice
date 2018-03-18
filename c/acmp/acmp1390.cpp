/* ACMP 1390 */
#include <cstdio>
#include <algorithm>

using namespace std;

struct E {
	int gf, gt;
	int vt;
	int id;
	E *next;
};

struct S {
	int vf, vt;
	E *e;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	E allee[n*4];
	E *e = allee;
	E *ee[n];
	fill(ee, ee+n, nullptr);
	for (int i=0; i<2*n; i++) {
		int gf, gt;
		scanf("%d%d", &gf, &gt);
		int vf = (gf-1)/4;
		int vt = (gt-1)/4;
		*e = E {gf, gt, vt, i, ee[vf]};
		ee[vf] = e++;
		*e = E {gt, gf, vf, i, ee[vt]};
		ee[vt] = e++;
	}
	bool e_seen[n*2];
	fill(e_seen, e_seen+2*n, false);
	S stack[n*4];
	int sz = 0;
	int cnt = 0;
	if (ee[0]) {
		stack[sz++] = S {0, ee[0]->vt, ee[0]};
		e_seen[ee[0]->id] = true;
		cnt++;
	}
	while (true) {
		S top = stack[sz-1];
		E *e;
		for (e=ee[top.vt]; e; e=e->next) {
			if (!e_seen[e->id]) {
				e_seen[e->id] = true;
				stack[sz++] = S {top.vt, e->vt, e};
				cnt++;
				break;
			}
		}
		if (e == nullptr)
			break;
	}
	if (cnt == n*2) {
		printf("Yes\n");
		for (int i=0; i<sz; i++)
			printf("%d %d ", stack[i].e->gf, stack[i].e->gt);
		printf("\n");
	} else {
		printf("No\n");
	}
}
