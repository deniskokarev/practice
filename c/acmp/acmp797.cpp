/* ACMP 797 */
#include <cstdio>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>
#include <cstring>
 
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
	inline bool covered() const {
		return covl & covr & 1;
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
					} else {
						cl[row][x][i] = cr[row][x][i] = true;
					}
				}
			}
		}
		for (int row=0; row<SZ; row++) {
			for (int x=0; x<SZ; x++) {
				uint8_t l = 0, r = 0;
				for (int i=0; i<k; i++) {
					l |= uint8_t(cl[row][x][i]) << i;
					r |= uint8_t(cr[row][x][i]) << i;
				}
				cache_cov_l[row][x] = l;
				cache_cov_r[row][x] = r;
			}
		}
	}
};
 
// "subtract" the segment [l,r] from remaining rows row, row+1,..,row+k-1
inline void upd_rows_rem(REM &rem, const CovCache &cc, int8_t row, int8_t l, int8_t r) {
	rem.covl |= cc.cache_cov_l[row][l];
	rem.covr |= cc.cache_cov_r[row][r];
}

struct Seen {
	int k;
	char seen[SZ][SZ][1<<10];
	Seen(int k):k(k) {
		assert(k<6);
		memset(seen, 0, sizeof(seen));
	}
	char &at(const P &p, const REM &rem) {
		assert(rem.covl < (1<<k) && rem.covr < (1<<k));
		int covidx = int(rem.covl)+(int(rem.covr)<<k);
		return seen[p.y][p.x][covidx];
	}
};

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
	Seen seen(k);
	queue<Q> qq;
	upd_rows_rem(f_rem, cc, 0, 0, k-1);
	qq.push(Q {0, P{0, 0}, f_rem});
	int ans = -1;
	while (!qq.empty()) {
		const Q q = qq.front();
		qq.pop();
		if (!q.rem.covered()) {
			REM nrl(q.rem), nrr(q.rem);
			for (int8_t dx=1; dx<SZ; dx++) {
				if (q.p.x-dx >= 0) {
					upd_rows_rem(nrl, cc, q.p.y, q.p.x-dx, q.p.x+k-1);
					auto &s = seen.at(P {int8_t(q.p.x-dx), q.p.y}, nrl);
					if (!s) {
						s = true;
						qq.push(Q { int16_t(q.dist+dx), P { int8_t(q.p.x-dx), q.p.y}, nrl});
					}
				} else if (q.p.x+dx+k <= SZ) {
					upd_rows_rem(nrr, cc, q.p.y, q.p.x, q.p.x+dx+k-1);
					auto &s = seen.at(P {int8_t(q.p.x+dx), q.p.y}, nrr);
					if (!s) {
						s = true;
						qq.push(Q { int16_t(q.dist+dx), P { int8_t(q.p.x+dx), q.p.y}, nrr});
					}
				}
			}
		} else {
			// done with row, just up
			REM nr(q.rem);
			if (q.p.y+1 < SZ) {
				nr.covl >>= 1;
				nr.covr >>= 1;
				upd_rows_rem(nr, cc, q.p.y+1, q.p.x, q.p.x+k-1);
				auto &s = seen.at(P {q.p.x, int8_t(q.p.y+1)}, nr);
				if (!s) {
					s = true;
					qq.push(Q { int16_t(q.dist+1), P { q.p.x, int8_t(q.p.y+1)}, nr});
				}
			} else {
				int over = q.p.y+k-1 - mxy;
				ans = q.dist-over;
				break;
			}
		}
	}
	assert(ans >= 0 && "there must be a solution");
	printf("%d\n", ans);
	return 0;
}
