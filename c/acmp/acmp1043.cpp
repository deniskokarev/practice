/* ACMP 1043 */
#include <stdio.h>
#include <string.h>
#include <math.h>

struct P {
	int x, y;
};

inline P operator+(const P a, const P b) {
	return P {a.x+b.x, a.y+b.y};
}

static const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	char brd[n+2][m+2];
	memset(brd, '.', sizeof(brd));
	for (int i=1; i<=n; i++) {
		scanf("%s", brd[i]+1); // risky trick
		brd[i][m+1] = '.';
	}
	int zone[n+2][m+2];
	memset(zone, 0, sizeof(zone));
	int qsz = 1 << (int)ceil(log2(n*m));
	int qmask = qsz-1;
	P qq[qsz];
	int nzone = 0;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			if (brd[i][j] == '*' && zone[i][j] == 0) {
				nzone++;
				int qh = 0;
				int qt = 0;
				P p = P {j, i};
				zone[p.y][p.x] = nzone;
				qq[qt++] = p;
				while (qh != qt) {
					auto nxt = qq[qh++];
					qh &= qmask;
					for (auto m:moves) {
						P nsq = nxt+m;
						if (brd[nsq.y][nsq.x] == '*' && zone[nsq.y][nsq.x] == 0) {
							qq[qt++] = nsq;
							qt &= qmask;
							zone[nsq.y][nsq.x] = nzone;
						}
					}
				}
			}
		}
	}
	printf("%d\n", nzone);
	return 0;
}
