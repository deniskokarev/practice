/* ACMP 129 */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

struct P {
	int8_t x, y;
};

inline P operator+(const P a, const P b) {
	return P {(int8_t)(a.x+b.x), (int8_t)(a.y+b.y)};
}

static const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	assert(n <= 100 && m <= 100);
	uint8_t dst[n+2][m+2];
	memset(dst, 0, sizeof(dst));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			dst[i][j] = UINT8_MAX;
	P ones[n*m];
	int onesz = 0;
	int d;
	for (int8_t i=1; i<=n; i++) {
		for (int8_t j=1; j<=m; j++) {
			scanf("%d", &d);
			if (d == 1)
				ones[onesz++] = P {j, i};
		}
	}
	int qsz = 1 << (int)ceil(log2((n+m)*2));
	int qmask = qsz-1;
	P qq[qsz];
	for (int i=0; i<onesz; i++) {
		int qh = 0;
		int qt = 0;
		auto &op = ones[i];
		qq[qt++] = op;
		dst[op.y][op.x] = 0;
		while (qh != qt) {
			auto nxt = qq[qh++];
			qh &= qmask;
			for (auto m:moves) {
				P nsq = nxt+m;
				if (dst[nsq.y][nsq.x] > dst[nxt.y][nxt.x]+1) {
					qq[qt++] = nsq;
					qt &= qmask;
					dst[nsq.y][nsq.x] = dst[nxt.y][nxt.x]+1;
				}
			}
		}
	}
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++)
			printf("%3d ", dst[i][j]);
		printf("\n");
	}
	return 0;
}
