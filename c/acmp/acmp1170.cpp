/* ACMP 1170 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MIN(A, B)	((A<B)?A:B)

struct P {
	int x, y;
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

// find min distance from src to any border and also distance to point dst
// we assume map has a bezel, where '.' means free point
unsigned mn_out(const char * const * const map, int n, int m, const P &src, const P &dst, unsigned *dst_len) {
	int qsz = 1<<int(ceil(log2(n*m+1)));
	int qmsk = qsz-1;
	unsigned dist[n+2][m+2];
	memset(dist, 0xff, sizeof(dist));
	dist[src.y][src.x] = 0;
	P qq[qsz];
	int qh, qt;
	qh = qt = 0;
	qq[qt++] = src;
	while (qh != qt) {
		const P p = qq[qh++]; qh &= qmsk;
		for (auto &m:moves) {
			const P np = P {p.x+m.x, p.y+m.y};
			if (map[np.y][np.x] == '.' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
				dist[np.y][np.x] = dist[p.y][p.x] + 1;
				qq[qt++] = np; qt &= qmsk;
			}
		}
	}
	*dst_len = dist[dst.y][dst.x];
	unsigned mn = UINT_MAX;
	for (int j=1; j<=m; j++)
		mn = MIN(mn, MIN(dist[1][j], dist[n][j]));
	for (int i=1; i<=n; i++)
		mn = MIN(mn, MIN(dist[i][1], dist[i][m]));
	if (mn < UINT_MAX)
		return mn+1;
	else
		return mn;
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	char map[n+2][m+2];
	memset(map, '#', sizeof(map));
	for (int i=1; i<=n; i++) {
		scanf("%s", map[i]+1); // dangerous, we don't limit length<=m
		map[i][m+1] = '#';
	}
	char *mm[n+2];
	for (int i=0; i<n+2; i++)
		mm[i] = map[i];
	P t {0, 0}, k {0, 0};
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			if (map[i][j] == 'T')
				t = P {j, i};
			else if (map[i][j] == 'K')
				k = P {j, i};
	map[t.y][t.x] = map[k.y][k.x] = '.';
	unsigned dist2key;
	unsigned mn = mn_out(mm, n, m, t, k, &dist2key);
	if (mn < UINT_MAX) {
		printf("%u\n", mn);
	} else {
		printf("No way");
		if (dist2key < UINT_MAX) {
			printf(" %u", dist2key);
			// unlock all doors
			for (int i=1; i<=n; i++)
				for (int j=1; j<=m; j++)
					if (map[i][j] == '-')
						map[i][j] = '.';
			mn = mn_out(mm, n, m, k, k, &dist2key); // dist2key will be unused
			if (mn < UINT_MAX)
				printf(" %u\n", mn);
			else
				printf(" No way\n");
		} else {
			printf(" No key\n");
		}
	}
	return 0;
}
