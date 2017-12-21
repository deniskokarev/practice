/* ACMP 1177 */
#include <stdio.h>

#define max(A,B) ((A>B)?A:B)
#define min(A,B) ((A<B)?A:B)

int floor_log2(unsigned n) {
	int cnt;
	for (cnt=-1; n; n>>=1,cnt++);
	return cnt;
}

constexpr int MXSZ = 1000;

// aggregate matrix
int ssum[MXSZ+1][MXSZ+1];
// multilevel min matrix
int aa[MXSZ][MXSZ];

int main(int argc, char **argv) {
	// read input
	int m, n, a, b, c, d;
	scanf("%d%d%d%d%d%d", &m, &n, &a, &b, &c, &d);
	// read and fill aggregate matrix
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			scanf("%d", &ssum[i][j]);
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			ssum[i][j] += ssum[i-1][j] + ssum[i][j-1] - ssum[i-1][j-1];
	// compute min matrix aa[][] where each aa[i][j] has min for rectangle aa[i][j]..aa[i+p2h][j+p2w]
	int w = a-c-2+1;
	int h = b-d-2+1;
	int l2w = floor_log2(w);
	int l2h = floor_log2(h);
	int p2w = 1<<l2w;
	int p2h = 1<<l2h;
	{
		int aa_loc[2][MXSZ][MXSZ];
		for (int i=0; i<=n-d; i++)
			for (int j=0; j<=m-c; j++)
				aa_loc[0][i][j] = ssum[i+d][j+c] - ssum[i+d][j] - ssum[i][j+c] + ssum[i][j];
		for (int l2j=1,p2j=1; l2j<=l2w; l2j++,p2j<<=1) {
			int prev = (l2j+1)&1;
			int cur = l2j&1;
			for (int i=0; i<n; i++)
				for (int j=0; j<=m-2*p2j; j++)
					aa_loc[cur][i][j] = min(aa_loc[prev][i][j], aa_loc[prev][i][j+p2j]);
		}
		for (int i=0; i<=n-d; i++)
			for (int j=0; j<=m-c; j++)
				aa_loc[0][i][j] = aa_loc[l2w&1][i][j];
		for (int l2i=1,p2i=1; l2i<=l2h; l2i++,p2i<<=1) {
			int prev = (l2i+1)&1;
			int cur = l2i&1;
			for (int i=0; i<=n-2*p2i; i++)
				for (int j=0; j<m; j++)
					aa_loc[cur][i][j] = min(aa_loc[prev][i][j], aa_loc[prev][i+p2i][j]);
		}
		for (int i=0; i<=n-d; i++)
			for (int j=0; j<=m-c; j++)
				aa[i][j] = aa_loc[l2h&1][i][j];
	}
	// find best answer
	int mx = -1;
	for (int i=0; i<=n-b; i++) {
		for (int j=0; j<=m-a; j++) {
			int s = ssum[i+b][j+a] - ssum[i+b][j] - ssum[i][j+a] + ssum[i][j];
			//fprintf(stderr, "%d ", s);
			int x1 = j+1, y1 = i+1, x2 = j+w, y2 = i+h;
			int mn_ul = aa[y1][x1];
			int mn_bl = aa[y2-p2h+1][x1];
			int mn_ur = aa[y1][x2-p2w+1];
			int mn_br = aa[y2-p2h+1][x2-p2w+1];
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
