/* ACMP 1391 */
#include <stdio.h>
#include <string.h>

struct E {
	int t;
	E *next;
};

void dfs(int i, int *comp, int compid, int *ord, unsigned &ordsz, const E * const *ee) {
	if (comp[i] == 0) {
		comp[i] = compid;
		for (auto e=ee[i]; e; e=e->next)
			dfs(e->t, comp, compid, ord, ordsz, ee);
		if (ord != nullptr)
			ord[ordsz++] = i;
	}
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	E allee[m*2];
	E *e = allee;
	E *eef[n]; // forw
	E *eer[n]; // rev
	memset(eef, 0, sizeof(eef));
	memset(eer, 0, sizeof(eer));
	for (int i=0; i<m; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		*e = E {t, eef[f]};
		eef[f] = e++;
		*e = E {f, eer[t]};
		eer[t] = e++;
	}
	// use connected component condensation approach
	int comp[n];
	int ordr[n];
	unsigned ordrsz = 0;
	memset(comp, 0, sizeof(comp));
	for (int i=0; i<n; i++)
		dfs(i, comp, 1, ordr, ordrsz, eef);
	int compid = 0;
	memset(comp, 0, sizeof(comp));
	for (int i=ordrsz-1; i>=0; i--) {
		int j = ordr[i];
		if (comp[j] == 0) {
			compid++;
			dfs(j, comp, compid, nullptr, ordrsz, eer);
		}
	}
	// no need to do actual condensation - the rev dfs walk
	// puts them in proper dependency order
	printf("%d\n", compid);
	for (int i=0; i<n; i++)
		printf("%d ", comp[i]);
	printf("\n");
	return 0;
}
