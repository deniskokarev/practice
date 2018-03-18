/* ACMP 761 */
#include <cstdio>
#include <algorithm>

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
	bool e_seen[m];
	fill(e_seen, e_seen+m, false);
	int cnt = 0;
	int loops = 0;
	while (cnt < m) {
		loops++;
		int stack[m+1];
		int stack_sz = 0;
		E *e = nullptr;
		for (int i=0; i<m*2; i++)
			if (!e_seen[allee[i].id] && (ecnt[allee[i].vf]&1)==1)
				e = &allee[i];
		if (!e)
			for (int i=0; i<m*2; i++)
				if (!e_seen[allee[i].id])
					e = &allee[i];
		if (e)
			stack[stack_sz++] = e->vf;
		while (stack_sz > 0) {
			int top = stack[stack_sz-1];
			E *e;
			for (e=ee[top]; e; e=e->next) {
				if (!e_seen[e->id]) {
					e_seen[e->id] = true;
					stack[stack_sz++] = e->vt;
					cnt++;
					ecnt[e->vf]--;
					ecnt[e->vt]--;
					break;
				}
			}
			if (e == nullptr)
				break;
		}
	}
	printf("%d\n", loops);
}
