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
	int loop = -1;
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
		int pl[n+1];
		int plsz = 0;
		pl[plsz++] = loop;
		for (int i=dd[loop].f; i>=0 && i!=loop; i=dd[i].f)
			pl[plsz++] = i;
		pl[plsz++] = loop;
		printf("YES\n%d\n", plsz);
		for (int j=plsz-1; j>=0; j--)
			printf("%d ", pl[j]+1);
		printf("\n");
	}
	return 0;
}
