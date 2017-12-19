/* ACMP 630 */
#include <stdio.h>
#include <memory.h>

constexpr int MXSZ = 10000;
constexpr int MXL2 = 14; // ceil(log2(MXSZ))

#define MAX(A,B)	((A>B)?A:B)
#define MIN(A,B)	((A<B)?A:B)

// precompute floor(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_floor_log2(int mx, unsigned char *ll) {
	ll[0] = 255; // undefined value
	ll[1] = 0;
	int i = 2;
	int l2, p2;
	for (l2=1,p2=2; i+p2<=mx; l2++,p2<<=1) {
		int j;
		for (j=0; j<p2; j++)
			ll[i+j] = l2;
		i += j;
	}
	while (i<=mx)
		ll[i++] = l2;
}

int main(int argc, char **argv) {
	unsigned char floor_log2[MXSZ+1];
	fill_floor_log2(MXSZ, floor_log2);
	int k;
	scanf("%d", &k);
	while (k-- > 0) {
		int l2 = MXL2+1;
		int aa[l2][MXSZ+1];
		memset(aa[0], 0, sizeof(aa[0]));
		int n;
		scanf("%d", &n);
		struct {
			int l, r;
		} pairs[n];
		for (int i=0; i<n; i++) {
			scanf("%d%d", &pairs[i].l, &pairs[i].r);
			aa[0][pairs[i].l]++;
			aa[0][pairs[i].r]--;
		}
		bool covered = true;
		for (int i=0; i<MXSZ; i++) {
			aa[0][i+1] += aa[0][i];
			covered &= (aa[0][i]>0);
		}
		if (covered) {
			for (int i=1,p2=1; i<l2; i++,p2<<=1)
				for (int j=0; j<=MXSZ; j++)
					if (j+p2<=MXSZ)
						aa[i][j] = MIN(aa[i-1][j], aa[i-1][j+p2]);
					else
						aa[i][j] = aa[i-1][j];
			bool can_remove = false;
			for (auto &p:pairs) {
				int l = p.l;
				int r = p.r-1;
				int len = r-l+1;
				int fl2 = floor_log2[len];
				int p2 = 1<<fl2;
				int mnl = aa[fl2][l];
				int mnr = aa[fl2][r-p2+1];
				int mn = MIN(mnl, mnr);
				//fprintf(stderr, "min(%d, %d) == %d\n", l, r, mn);
				if (mn > 1) {
					can_remove = true;
					break;
				}
			}
			if (!can_remove)
				printf("Accepted\n");
			else
				printf("Wrong Answer\n");
		} else {
			printf("Accepted\n");
		}
	}
	return 0;
}
