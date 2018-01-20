/* ACMP 1365 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MSZ 1000
#define __str(a) #a
#define str(a) __str(a)

struct P {
	short int x, y;
	inline P operator+(const P &b) const {
		return P {(short int)(x+b.x), (short int)(y+b.y)};
	}
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	char map[MSZ+2][MSZ+2];
	unsigned dist[MSZ+2][MSZ+2];
	memset(map, '#', sizeof(map));
	memset(dist, 0xff, sizeof(dist));
	short int n, m;
	P start, end;
	scanf("%hd%hd%hd%hd%hd%hd", &n, &m, &start.y, &start.x, &end.y, &end.x);
	assert(n > 0 && m > 0 && start.x > 0 && start.y > 0 && end.x > 0 && end.y > 0);
	assert(n <= MSZ && m <= MSZ && start.x <= MSZ && start.y <= MSZ && end.x <= MSZ && end.y <= MSZ);
	for (int i=1; i<=n; i++)
		scanf("%" str(MSZ) "s", map[i]+1);
	dist[start.y][start.x] = 0;
    const int qsz = 1<<(int)ceil(log2((n+2)*(m+2)));
    const int qmask = qsz-1;
    P qq[qsz];
    int h = 0, t = 0;
    qq[t++] = start;
	while (h != t) {
		const P p = qq[h++];
		h &= qmask;
		const unsigned d = dist[p.y][p.x];
		for (auto m:moves) {
			const P np = p + m;
			unsigned &nd = dist[np.y][np.x];
			if (map[np.y][np.x] == '.' && nd > d+1) {
				nd = d+1;
				qq[t++] = np;
				t &= qmask;
			} else if (map[np.y][np.x] == 'W' && nd > d+2) {
				nd = d+2;
				qq[t++] = np;
				t &= qmask;
			}
		}
	}
	int ans = (int)dist[end.y][end.x];
	printf("%d\n", ans);
	return 0;
}
