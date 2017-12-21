/* ACMP 1177 */
#include <stdio.h>
#include <limits.h>
#include <vector>

using namespace std;

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
	// read input
	int m, n, a, b, c, d;
	scanf("%d%d%d%d%d%d", &m, &n, &a, &b, &c, &d);
	// precompute log2s
	int mxsz = max(n, m);
	unsigned char floor_log2[mxsz+1];
	unsigned char ceil_log2[mxsz+1];
	fill_floor_log2(mxsz, floor_log2);
	fill_ceil_log2(mxsz, ceil_log2);
	// read and fill aggregate matrix
	vector<vector<int>> ssum(n+1, vector<int>(m+1));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			scanf("%d", &ssum[i][j]);
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			ssum[i][j] += ssum[i-1][j] + ssum[i][j-1] - ssum[i-1][j-1];
			//fprintf(stderr, "%d ", ssum[i][j]);
		}
		//fprintf(stderr, "\n");
	}
	// multilevel min matrix
	//int aa[l2n][l2m][n][m];
	int w = a-c-2+1;
	int h = b-d-2+1;
	int l2w = floor_log2[w];
	int l2h = floor_log2[h];
	vector<vector<vector<vector<int>>>> aa = \
		vector<vector<vector<vector<int>>>>(l2h+1, vector<vector<vector<int>>>(l2w+1));
	aa[0][0] = vector<vector<int>>(n, vector<int>(m, INT_MIN));
	for (int i=0; i<=n-d; i++) {
		for (int j=0; j<=m-c; j++) {
			aa[0][0][i][j] = ssum[i+d][j+c] - ssum[i+d][j] - ssum[i][j+c] + ssum[i][j];
			//fprintf(stderr, "%d ", aa[0][0][i][j]);
		}
		//fprintf(stderr, "\n");
	}
	// fill 0-level for each row
	for (int l2j=1,p2j=1; l2j<=l2w; l2j++,p2j<<=1) {
		aa[0][l2j] = vector<vector<int>>(n, vector<int>(m));
		for (int i=0; i<n; i++)
			for (int j=0; j<=m-2*p2j; j++)
				aa[0][l2j][i][j] = min(aa[0][l2j-1][i][j], aa[0][l2j-1][i][j+p2j]);
	}
	// fill 0-level for each col
	for (int l2i=1,p2i=1; l2i<=l2h; l2i++,p2i<<=1) {
		aa[l2i][0] = vector<vector<int>>(n, vector<int>(m));
		for (int i=0; i<=n-2*p2i; i++)
			for (int j=0; j<m; j++)
				aa[l2i][0][i][j] = min(aa[l2i-1][0][i][j], aa[l2i-1][0][i+p2i][j]);
	}
	// fill all levels for upto l2 hight and l2 width
	for (int l2i=1,p2i=1; l2i<=l2h; l2i++,p2i<<=1) {
		for (int l2j=1,p2j=1; l2j<=l2w; l2j++,p2j<<=1) {
			aa[l2i][l2j] = vector<vector<int>>(n, vector<int>(m));
			for (int i=0; i<=n-2*p2i; i++) {
				for (int j=0; j<=m-2*p2j; j++) {
					int a = aa[l2i-1][l2j-1][i][j];
					a = min(a, aa[l2i-1][l2j-1][i+p2i][j]);
					a = min(a, aa[l2i-1][l2j-1][i][j+p2j]);
					a = min(a, aa[l2i-1][l2j-1][i+p2i][j+p2j]);
					aa[l2i][l2j][i][j] = a;
				}
			}
			aa[l2i-1][l2j-1] = vector<vector<int>>(); // release prior result
		}
	}
	int p2w = 1<<l2w;
	int p2h = 1<<l2h;
	// find best answer
	int mx = INT_MIN;
	for (int i=0; i<=n-b; i++) {
		for (int j=0; j<=m-a; j++) {
			int s = ssum[i+b][j+a] - ssum[i+b][j] - ssum[i][j+a] + ssum[i][j];
			//fprintf(stderr, "%d ", s);
			int x1 = j+1, y1 = i+1, x2 = j+w, y2 = i+h;
			int mn_ul = aa[l2h][l2w][y1][x1];
			int mn_bl = aa[l2h][l2w][y2-p2h+1][x1];
			int mn_ur = aa[l2h][l2w][y1][x2-p2w+1];
			int mn_br = aa[l2h][l2w][y2-p2h+1][x2-p2w+1];
			//fprintf(stderr, "min ul: %d bl: %d ur: %d br: %d\n", mn_ul, mn_bl, mn_ur, mn_br);
			int mn = mn_ul;
			mn = min(mn, mn_bl);
			mn = min(mn, mn_ur);
			mn = min(mn, mn_br);
			//fprintf(stderr, "%d ", mn);
			mx = max(mx, s-mn);
		}
		//fprintf(stderr, "\n");
	}
	printf("%d\n", mx);
	return 0;
}
