#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cstdio>
#include <cinttypes>
#include <string>
#include <vector>
/* Hackerrank https://www.hackerrank.com/challenges/cube-summation */
using namespace std;

// 3d fenwick

using CUBE = vector<vector<vector<int64_t>>>;

inline CUBE mkcube(int n) {
	return CUBE(n, vector<vector<int64_t>>(n, vector<int64_t>(n)));
}

void fw3d_inc(CUBE &fw3d, int n, int x, int y, int z, int64_t d) {
	for (int i=z; i<n; i|=i+1)
		for (int j=y; j<n; j|=j+1)
			for (int k=x; k<n; k|=k+1)
				fw3d[i][j][k] += d;
}

inline int64_t fw3d_sum_axis(const CUBE &fw3d, int n, int x, int y, int z) {
	int64_t s = 0;
	for (int i=z; i>=0; i=(i&(i+1))-1)
		for (int j=y; j>=0; j=(j&(j+1))-1)
			for (int k=x; k>=0; k=(k&(k+1))-1)
				s += fw3d[i][j][k];
	return s;
}

int64_t fw3d_sum(const CUBE &fw3d, int n, int x1, int x2, int y1, int y2, int z1, int z2) {
	int64_t s = 0;
	s += fw3d_sum_axis(fw3d, n, x2, y2, z2);
	s += fw3d_sum_axis(fw3d, n, x2, y1, z1);
	s += fw3d_sum_axis(fw3d, n, x1, y2, z1);
	s += fw3d_sum_axis(fw3d, n, x1, y1, z2);
	s -= fw3d_sum_axis(fw3d, n, x1, y1, z1);
	s -= fw3d_sum_axis(fw3d, n, x1, y2, z2);
	s -= fw3d_sum_axis(fw3d, n, x2, y1, z2);
	s -= fw3d_sum_axis(fw3d, n, x2, y2, z1);
	return s;
}


int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		scanf("%d%d", &n, &m);
		CUBE fw3d = mkcube(n);
		CUBE cube = mkcube(n);
		while (m--) {
			char q[32];
			scanf("%32s", q);
			if (q[0] == 'U') {
				// update
				int x, y, z, w;
				scanf("%d%d%d%d", &x, &y, &z, &w);
				x--, y--, z--;
				int64_t d = w;
				d -= cube[x][y][z];
				cube[x][y][z] = w;
				fw3d_inc(fw3d, n, x, y, z, d);
			} else {
				// query
				int x1, y1, z1, x2, y2, z2;
				scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
				x1 -= 2, y1 -= 2, z1 -= 2, x2--, y2--, z2--;
				printf("%" PRId64 "\n", fw3d_sum(fw3d, n, x1, x2, y1, y2, z1, z2));
			}
		}
	}
	return 0;
}
