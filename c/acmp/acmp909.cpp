/* ACMP 909 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

constexpr int MSZ = 1000;

struct P {
	short x, y;
};

inline P operator+(const P a, const P b) {
	return P {(short)(a.x+b.x), (short)(a.y+b.y)};
}

using ZSTAT = struct {
	int s_cnt;
	int x_cnt;
};

static const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static char brd[MSZ+2][MSZ+2];
static int zone[MSZ+2][MSZ+2];
static ZSTAT zstat[MSZ*(MSZ+1)/2+1];
constexpr int qsz = 1<<20;
static int qmask = qsz-1;
static P qq[qsz];

inline void update_stat(char p, ZSTAT &zs) {
	switch (p) {
	case 'X':
		zs.x_cnt++;
		break;
	case 'S':
		zs.s_cnt++;
		break;
	default:
		assert(false && "p has to be only X or S");
	}
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	assert(n <= MSZ && m <= MSZ);
	memset(brd[0], '-', sizeof(brd[0]));
	memset(brd[n+1], '-', sizeof(brd[0]));
	for (int i=1; i<=n; i++) {
		scanf("%s", brd[i]+1); // risky trick
		brd[i][0] = brd[i][m+1] = '-';
	}
	int nzone = 0;
	for (short i=1; i<=n; i++) {
		for (short j=1; j<=m; j++) {
			if (brd[i][j] != '-' && zone[i][j] == 0) {
				nzone++;
				int qh = 0;
				int qt = 0;
				P p = P {j, i};
				zone[p.y][p.x] = nzone;
				update_stat(brd[i][j], zstat[nzone]);
				qq[qt++] = p;
				while (qh != qt) {
					auto nxt = qq[qh++];
					qh &= qmask;
					for (auto m:moves) {
						P nsq = nxt+m;
						if (brd[nsq.y][nsq.x] != '-' && zone[nsq.y][nsq.x] == 0) {
							qq[qt++] = nsq;
							qt &= qmask;
							zone[nsq.y][nsq.x] = nzone;
							update_stat(brd[nsq.y][nsq.x], zstat[nzone]);
						}
					}
				}
			}
		}
	}
	int a1 = 0, a2 = 0, a3 = 0; // clear, damaged, killed
	for (int i=1; i<=nzone; i++) {
		if (zstat[i].s_cnt > 0) {
			if (zstat[i].x_cnt <= 0)
				a1++;
			else
				a2++;
		} else {
			a3++;
		}
	}
	printf("%d %d %d\n", a1, a2, a3);
	return 0;
}
