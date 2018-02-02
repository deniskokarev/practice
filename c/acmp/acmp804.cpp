/* ACMP 804 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct P {
	short x, y;
	P operator+(const P b) const {
		return P {(short)(x+b.x), (short)(y+b.y)};
	}
};

static const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	// row,col -> dist
	char brd[n][m];
	for (int i=0; i<n; i++)
		scanf("%s", brd[i]); // risky trick
	P pp[2] = {{1, 1}, {1, 1}};
	for (short i=0; i<n; i++)
		for (short j=0; j<m; j++)
			if (brd[i][j] == 'T')
				pp[1] = P {j, i};
	int qsz = 1<<(int)(ceil(log2(n*m+1)));
	int qszmask = qsz-1;
	int res[2] = {-1, -1};
	for (int color=0; color<2; color++) {
		int dist[n][m];
		for (int i=0; i<n; i++)
			for (int j=0; j<m; j++)
				dist[i][j] = dist[i][j] = INT_MAX;
		P qq[qsz];
		int h = 0, t = 0;
		qq[t++] = pp[color];
		dist[pp[color].y][pp[color].x] = 0;
		while (h != t) {
			const P &p = qq[h++];
			h &= qszmask;
			for (auto &m:moves) {
				const P np = p+m;
				if (brd[np.y][np.x] != '#' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
					dist[np.y][np.x] = dist[p.y][p.x]+1;
					qq[t++] = np;
					t &= qszmask;
				}
			}
		}
		res[color] = dist[n-2][m-2];
	}
	printf("%d\n%s\n", res[0], (res[0]<res[1])?"Yes":"No");
	return 0;
}
