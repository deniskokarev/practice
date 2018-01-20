/* ACMP 1365 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MSZ 1000
#define __str(a) #a
#define str(a) __str(a)

struct P {
	int x, y;
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	char map[MSZ+2][MSZ+2];
	memset(map, '#', sizeof(map));
	unsigned dist[MSZ+2][MSZ+2];
	memset(dist, 0xff, sizeof(dist));
	int n, m;
	P start, end;
	scanf("%d%d%d%d%d%d", &n, &m, &start.y, &start.x, &end.y, &end.x);
	assert(n > 0 && m > 0 && start.x > 0 && start.y > 0 && end.x > 0 && end.y > 0);
	assert(n <= MSZ && m <= MSZ && start.x <= MSZ && start.y <= MSZ && end.x <= MSZ && end.y <= MSZ);
	for (int i=1; i<=n; i++)
		scanf("%" str(MSZ) "s", map[i]+1);
	dist[start.y][start.x] = 0;
	P qq[(n+1)*(m+1)];
	int h = 0, t = 0;
	qq[t++] = start;
	while (h != t) {
		const P &p = qq[h];
		if (map[p.y][p.x] != '#') {
			for (auto &m:moves) {
				const P np = {p.x+m.x, p.y+m.y};
				if (map[np.y][np.x] == '.' && dist[np.y][np.x] > dist[p.y][p.x]+1) {
					dist[np.y][np.x] = dist[p.y][p.x]+1;
					qq[t++] = np;
				} else if (map[np.y][np.x] == 'W' && dist[np.y][np.x] > dist[p.y][p.x]+2) {
					dist[np.y][np.x] = dist[p.y][p.x]+2;
					qq[t++] = np;
				}
			}
		}
		h++;
	}
	int ans = (int)dist[end.y][end.x];
	printf("%d\n", ans);
	return 0;
}
