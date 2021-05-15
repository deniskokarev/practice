/* ACMP 690 */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <climits>

using namespace std;

constexpr int SZ = 100;

#define dim(X)	(int(sizeof(X)/sizeof(X[0])))

struct P {
	int x, y;
};

const static P moves[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

inline int warnsdorff_score(int map[SZ+4][SZ+4], const P &p) {
	if (map[p.y][p.x])
		return INT_MAX;
	int cnt = 0;
	if (map[p.y][p.x] == 0) {
		for (const auto &m:moves) {
			P np {p.x+m.x, p.y+m.y};
			if (map[np.y][np.x] == 0)
				cnt++;
		}
	}
	return cnt;
}

// straight walk using W-heuristic without backtracking
bool warnsdorff_straight_walk(int map[SZ+4][SZ+4], const P &p, int wdep, int idx) {
	if (map[p.y][p.x] != 0)
		return false;
	map[p.y][p.x] = idx;
	if (wdep <= 1) {
		return true;
	} else {
		struct WSC {
			int wsc;
			P m;
			bool operator<(const WSC &b) const {
				return wsc < b.wsc;
			}
		} min_mv {INT_MAX};
		for (const P &mv:moves) {
			const P nxt_mv = P {p.x+mv.x, p.y+mv.y};
			min_mv = min(min_mv, {warnsdorff_score(map, nxt_mv), nxt_mv});
		}
		if (warnsdorff_straight_walk(map, min_mv.m, wdep-1, idx+1)) {
			return true;
		} else {
			map[p.y][p.x] = 0;
			return false;
		}
	}
}

// doing dumb dfs to the depth of dfs_depth
// from where trying straight warnsdorff walk
bool dfs_then_warnsdorff_walk(int map[SZ+4][SZ+4], const P &p, int dfs_dep, int wdep, int idx) {
	if (map[p.y][p.x] != 0)
		return false;
	if (!dfs_dep) {
		return warnsdorff_straight_walk(map, p, wdep, idx);
	} else {
		map[p.y][p.x] = idx;
		for (const P &mv:moves) {
			const P nxt_mv = P {p.x+mv.x, p.y+mv.y};
			if (dfs_then_warnsdorff_walk(map, nxt_mv, dfs_dep-1, wdep-1, idx+1))
				return true;
		}
		map[p.y][p.x] = 0;
		return false;
	}
}

int main(int argc, char **argv) {
	int map[SZ+4][SZ+4];
	int n, m;
	fscanf(stdin, "%d%d\n", &n, &m);
	assert(n <= SZ && m <= SZ);
	P start {2, 2};
	for (int i=0; i<dim(map); i++)
		for (int j=0; j<dim(map[0]); j++)
			map[i][j] = -1;
	int cnt = 0;
	for (int y=2; y<n+2; y++) {
		for (int x=2; x<m+2 && !feof(stdin); x++) {
			int c = fgetc(stdin);
			switch(c) {
			case 'K':
				start = P {x, y};
			case '.':
				map[y][x] = 0;
				cnt++;
				break;
			}
		}
		fgetc(stdin); // \n
	}
	if (dfs_then_warnsdorff_walk(map, start, 2, cnt, 1)) {
		for (int y=2; y<n+2; y++) {
			for (int x=2; x<m+2; x++)
				printf("%2d ", (map[y][x] > 0)?map[y][x]:0);
			printf("\n");
		}
	} else {
		assert(false && "hmm, suppose to have a solution");
	}
	return 0;
}
