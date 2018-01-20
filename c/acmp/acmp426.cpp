/* ACMP 426 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MSZ 250
#define str(a) __str(a)
#define __str(a) #a

struct P {
	int x, y;
	bool operator==(const P &b) const {
		return x == b.x && y == b.y;
	}
};

const P moves[] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	assert(n <= MSZ);
	char map[MSZ+2][MSZ+2];
	P path[MSZ+2][MSZ+2];
	P beg {-1, -1};
	memset(map, 0, sizeof(map));
	for (int i=1; i<=n; i++) {
		char ln[MSZ+1];
		scanf("%" str(MSZ) "s", ln);
		for (int j=0; j<n; j++) {
			map[i][j+1] = ln[j];
			path[i][j+1] = P {-1, -1};
			if (ln[j] == '@')
				beg = P {j+1, i};
		}
	}
	assert(beg.x >= 0 && beg.x <= MSZ && beg.y >= 0 && beg.y <= MSZ);
	map[beg.y][beg.x] = '.';
	path[beg.y][beg.x] = P {MSZ+1, MSZ+1};
	int qsz = 1<<(int)ceil(log2((n+1)*(n+1)));
	int qmask = qsz-1;
	P qq[qsz];
	int h = 0, t = 0;
	qq[t++] = beg;
	P ans {-1, -1};
	while (h != t) {
		const P &p = qq[h++];
		h &= qmask;
		if (map[p.y][p.x] == 'X') {
			ans = p;
			break;
		} else if (map[p.y][p.x] == '.') {
			for (const auto &m:moves) {
				P np = P {p.x+m.x, p.y+m.y};
				if (path[np.y][np.x].x < 0) {
					qq[t++] = np;
					t &= qmask;
					path[np.y][np.x] = p;
				}
			}
		}
	}
	if (map[ans.y][ans.x] == 'X') {
		for (;ans.x <= MSZ; ans = path[ans.y][ans.x])
			map[ans.y][ans.x] = '+';
		printf("Y\n");
		map[beg.y][beg.x] = '@';
		for (int i=1; i<=n; i++)
			printf("%s\n", map[i]+1);
	} else {
		printf("N\n");
	}
	return 0;
}
