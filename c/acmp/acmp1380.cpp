/* ACMP 1380 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

struct D {
	int w, f;
};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			scanf("%d", &mm[i][j]);
			if (mm[i][j] >= 100000)
				mm[i][j] = DINF;
		}
	}
	// ford with pathes
	D dd[n];
	fill(dd, dd+n, D {DINF, -1});
	dd[0] = D {0, -1};
	int loop = -1;	// the path from 0->loop has a loop somewhere in between
	for (int v=0; v<n; v++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				int nw = dd[i].w+mm[i][j];
				if (nw < -DINF) {
					loop = j;
					goto end;
				}
				if (dd[j].w > nw) {
					dd[j].w = nw;
					dd[j].f = i;
				}
			}
		}
	}
	// ford one last time
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int nw = dd[i].w+mm[i][j];
			if (nw < -DINF) {
				loop = j;
				goto end;
			}
			if (dd[j].w > nw) {
				dd[j].w = nw;
				dd[j].f = i;
				loop = j;
				goto end;
			}
		}
	}
 end:
	if (loop < 0) {
		printf("NO\n");
	} else {
		int seen[n];
		fill(seen, seen+n, 0);
		int lbeg; // find beginning of the loop when going back from loop->0 
		for (lbeg=loop; !seen[lbeg]; lbeg=dd[lbeg].f)
			seen[lbeg] = 1;
		int pl[n+1];
		int plsz = 0;
		pl[plsz++] = lbeg;
		for (int i=dd[lbeg].f; i!=lbeg; i=dd[i].f)
			pl[plsz++] = i;
		pl[plsz++] = lbeg;
		printf("YES\n%d\n", plsz);
		for (int j=plsz-1; j>=0; j--)
			printf("%d ", pl[j]+1);
		printf("\n");
	}
	return 0;
}
