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
	S ans[n*4];
	int stack_sz = 0, ans_sz = 0;;
	int cnt = 0;
	if (ee[0]) {
		stack[stack_sz++] = S {0, ee[0]->vt, ee[0]};
		e_seen[ee[0]->id] = true;
		cnt++;
	}
	while (stack_sz > 0) {
		S top = stack[stack_sz-1];
		E *e;
		for (e=ee[top.vt]; e; e=e->next) {
			if (!e_seen[e->id]) {
				e_seen[e->id] = true;
				stack[stack_sz++] = S {top.vt, e->vt, e};
				cnt++;
				break;
			}
		}
		if (e == nullptr) {
			ans[ans_sz++] = top;
			stack_sz--;
		}
	}
	if (cnt == n*2 && ans[0].vt == 0) {
		printf("Yes\n");
		for (int i=ans_sz-1; i>=0; i--)
			printf("%d %d ", ans[i].e->gf, ans[i].e->gt);
		printf("\n");
	} else {
		printf("No\n");
	}
}
