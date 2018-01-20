/* ACMP 1365 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MSZ 1000

struct P {
	short int x, y;
	unsigned dist;
};

const P moves[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(int argc, char **argv) {
	char map[MSZ+2][MSZ+2];
	unsigned dist[MSZ+2][MSZ+2];
	memset(map, 0, sizeof(map));
	memset(dist, 0xff, sizeof(dist));
	short int n, m;
	P start {0, 0, 0}, end {0, 0, 0};
	scanf("%hd%hd%hd%hd%hd%hd", &n, &m, &start.y, &start.x, &end.y, &end.x);
	assert(n > 0 && m > 0 && start.x > 0 && start.y > 0 && end.x > 0 && end.y > 0);
	assert(n <= MSZ && m <= MSZ && start.x <= MSZ && start.y <= MSZ && end.x <= MSZ && end.y <= MSZ);
	while (!feof(stdin) && fgetc(stdin) != '\n');
	for (int i=1; i<=n; i++) {
		int rc = fread(map[i]+1, 1, m, stdin);
		assert(rc == m);
		int c = fgetc(stdin);
		assert(c == '\n');
	}
	dist[start.y][start.x] = 0;
    const int hsz = 1<<(int)ceil(log2((n+2)*(m+2)));
    P heap[hsz];
    int t = 0;
    heap[t++] = start;
	while (t > 0) {
		const P p = heap[0]; t--;
		heap[0] = heap[t];
		for (int h=0; h*2+1<t; ) {
			int l = h*2+1, r = h*2+2;
			int m = (r < t && heap[r].dist < heap[l].dist)?r:l;
			if (heap[h].dist > heap[m].dist) {
				P c = heap[h];
				heap[h] = heap[m];
				heap[m] = c;
				h = m;
			} else {
				break;
			}
		}
		const unsigned d = dist[p.y][p.x];
		for (const auto &m:moves) {
			P np = P {(short int)(p.x+m.x), (short int)(p.y+m.y), d+1};
			unsigned &nd = dist[np.y][np.x];
			if (map[np.y][np.x] == '.' && nd > d+1) {
				nd = d+1;
			} else if (map[np.y][np.x] == 'W' && nd > d+2) {
				nd = d+2;
				np.dist++;
			} else {
				continue;
			}
			heap[t++] = np;
			for (int n=t-1, r=(n-1)/2; n>0; n=r) {
				if (heap[r].dist > heap[n].dist) {
					P c = heap[r];
					heap[r] = heap[n];
					heap[n] = c;
				} else {
					break;
				}
			}
		}
	}
	int ans = (int)dist[end.y][end.x];
	printf("%d\n", ans);
	return 0;
}
