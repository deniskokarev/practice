/* ACMP 797 */
#include <cstdio>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>
#include <bitset>

using namespace std;

constexpr int SZ = 50;

struct P {
	int8_t x, y;
};

struct IR {
	int8_t l, r;
	operator bool() const {
		return l != INT8_MAX;
	}
};

struct REM { // rows remaining
	uint8_t covl, covr; // care only if next 8 rows are fully covered from the left and right
	inline bool covered(int8_t y) const {
		uint8_t i = uint8_t(1)<<(y&7);
		return covl & covr & i;
	}
};

struct Q {
	int16_t dist;
	P p;
	REM rem;
	bool operator<(const Q &q) const {
		return dist > q.dist;
	}
};

struct CovCache {
	uint8_t cache_cov_l[SZ][SZ];
	uint8_t cache_cov_r[SZ][SZ];
	CovCache(const IR allrows[SZ], int k) {
		vector<vector<vector<bool>>> cl(SZ, vector<vector<bool>>(SZ, vector<bool>(8, false)));
		vector<vector<vector<bool>>> cr(SZ, vector<vector<bool>>(SZ, vector<bool>(8, false)));
		for (int row=0; row<SZ; row++) {
			for (int x=0; x<SZ; x++) {
				for (int i=0; i<8; i++) {
					int y = row+i;
					if (y<SZ) {
						cl[row][x][i] = (x <= allrows[y].l);
						cr[row][x][i] = (allrows[y].r <= x);
					}
				}
			}
		}
		for (int row=0; row<SZ; row++) {
			for (int x=0; x<SZ; x++) {
				uint8_t l = 0, r = 0;
				for (int i=0; i<k; i++) {
					int b_pos = (row+i) & 7;
					l |= uint8_t(cl[row][x][i]) << b_pos;
					r |= uint8_t(cr[row][x][i]) << b_pos;
				}
				cache_cov_l[row][x] = l;
				cache_cov_r[row][x] = r;
			}
		}
	}
};

// "subtract" the segment [l,r] from remaining rows row, row+1,..,row+k-1
inline void upd_rows_rem(REM &rem, const CovCache &cc, int row, int8_t l, int8_t r) {
	rem.covl |= cc.cache_cov_l[row][l];
	rem.covr |= cc.cache_cov_r[row][r];
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d%d", &n, &k);
	assert(k<6);
	int8_t mxy = 0;
	// left/right x for each y
	IR allrows[SZ];
	fill(allrows, allrows+SZ, IR {INT8_MAX, INT8_MIN});
	for (int i=0; i<n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		mxy = max(mxy, int8_t(y));
		allrows[y] = IR {min(allrows[y].l, int8_t(x)), max(allrows[y].r, int8_t(x))};
	}
	CovCache cc(allrows, k);
	REM f_rem {0, 0};
	priority_queue<Q> qq;
	upd_rows_rem(f_rem, cc, 0, 0, k-1);
	qq.push(Q {0, P{0, 0}, f_rem});
	while (!qq.empty()) {
		const Q q = qq.top();
		if (q.p.y >= SZ)
			break;
		qq.pop();
		if (!q.rem.covered(q.p.y)) {
			if (q.p.x > allrows[q.p.y].l) {
				REM nr(q.rem);
				upd_rows_rem(nr, cc, q.p.y, allrows[q.p.y].l, q.p.x+k-1);
				qq.push(Q { int16_t(q.dist+(q.p.x-allrows[q.p.y].l)), P { allrows[q.p.y].l, q.p.y}, nr});
			}
			if (q.p.x+k-1 < allrows[q.p.y].r) {
				REM nr(q.rem);
				upd_rows_rem(nr, cc, q.p.y, q.p.x, allrows[q.p.y].r);
				qq.push(Q { int16_t(q.dist+(allrows[q.p.y].r-q.p.x-k+1)), P { int8_t(allrows[q.p.y].r-k+1), q.p.y}, nr});
			}
		} else {
			// done with row, just up
			REM nr(q.rem);
			if (q.p.y+8 < SZ) {
				nr.covl &= ~((uint8_t(1) << (q.p.y&7)));
				nr.covr &= ~((uint8_t(1) << (q.p.y&7)));
			}
			upd_rows_rem(nr, cc, q.p.y+1, q.p.x, q.p.x+k-1);
			qq.push(Q { int16_t(q.dist+1), P { q.p.x, int8_t(q.p.y+1)}, nr});
		}
	}
	assert(!qq.empty() && "there must be a solution");
	const Q &top = qq.top();
	int over = top.p.y+k-1 - mxy;
	if (over < 0 || top.p.y == 0)
		over = 0;
	printf("%d\n", top.dist-over);
	return 0;
}
