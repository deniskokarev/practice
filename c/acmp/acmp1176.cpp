/* ACMP 1176 */
#include <stdio.h>

constexpr int MXSZ = 300;

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

// precompute ceil(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_ceil_log2(int mx, unsigned char *ll) {
	fill_floor_log2(mx, ll);
	for (int i=1; i<=mx; i++)
		ll[i]++;
	for (int p2=1; p2<=mx; p2<<=1)
		ll[p2]--;
}

int main(int argc, char **argv) {
	// precompute log2s
	unsigned char floor_log2[MXSZ+1];
	unsigned char ceil_log2[MXSZ+1];
	fill_floor_log2(MXSZ, floor_log2);
	fill_ceil_log2(MXSZ, ceil_log2);
	// read input
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	int l2n = ceil_log2[n]+1;
	int l2m = ceil_log2[m]+1;
	int aa[l2n][l2m][n][m];
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			scanf("%d", &aa[0][0][i][j]);
	// fill 0-level for each row
	for (int l2j=1,p2j=1; l2j<l2m; l2j++,p2j<<=1)
		for (int i=0; i<n; i++)
			for (int j=0; j<m; j++)
				if (j+p2j<m)
					aa[0][l2j][i][j] = MIN(aa[0][l2j-1][i][j], aa[0][l2j-1][i][j+p2j]);
				else
					aa[0][l2j][i][j] = aa[0][l2j-1][i][j];
	// fill all levels for all rows
	for (int l2i=1,p2i=1; l2i<l2n; l2i++,p2i<<=1) {
		for (int l2j=1,p2j=1; l2j<l2m; l2j++,p2j<<=1) {
			for (int i=0; i<n; i++) {
				for (int j=0; j<m; j++) {
					int a = aa[l2i-1][l2j-1][i][j];
					if (i+p2i<n)
						a = MIN(a, aa[l2i-1][l2j-1][i+p2i][j]);
					if (j+p2j<m)
						a = MIN(a, aa[l2i-1][l2j-1][i][j+p2j]);
					if (i+p2i<n && j+p2j<m)
						a = MIN(a, aa[l2i-1][l2j-1][i+p2i][j+p2j]);
					aa[l2i][l2j][i][j] = a;
				}
			}
		}
	}
	while (k-- > 0) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
		x1--, y1--, x2--, y2--;
		int w = x2-x1+1;
		int h = y2-y1+1;
		int l2w = floor_log2[w];
		int l2h = floor_log2[h];
		int p2w = 1<<l2w;
		int p2h = 1<<l2h;
		int mn_ul = aa[l2h][l2w][y1][x1];
		int mn_bl = aa[l2h][l2w][y2-p2h+1][x1];
		int mn_ur = aa[l2h][l2w][y1][x2-p2w+1];
		int mn_br = aa[l2h][l2w][y2-p2h+1][x2-p2w+1];
		//fprintf(stderr, "min ul: %d bl: %d ur: %d br: %d\n", mn_ul, mn_bl, mn_ur, mn_br);
		int mn = mn_ul;
		mn = MIN(mn, mn_bl);
		mn = MIN(mn, mn_ur);
		mn = MIN(mn, mn_br);
		printf("%d\n", mn);
	}
	return 0;
}
