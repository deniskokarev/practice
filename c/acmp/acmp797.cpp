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
 
struct REM { // coverage of k rows ahead
	uint8_t covl, covr; // left and right ends coverage
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

// left and right ends coverage for next k rows
struct CovCache {
	uint8_t cache_cov_l[SZ][SZ];
	uint8_t cache_cov_r[SZ][SZ];
	uint8_t all_cov;
	CovCache(const IR allrows[SZ], int k) {
		all_cov = (uint8_t(1) << k)-1;
		vector<vector<vector<bool>>> cl(SZ, vector<vector<bool>>(SZ, vector<bool>(k, false)));
		vector<vector<vector<bool>>> cr(SZ, vector<vector<bool>>(SZ, vector<bool>(k, false)));
		for (int row=0; row<SZ; row++) {
			for (int x=0; x<SZ; x++) {
				for (int i=0; i<k; i++) {
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
 
// cover next k rows if our cursor stretch from [l..r] inclusive
// @return true if something was taken
inline bool upd_rows_rem(REM &rem, const CovCache &cc, int8_t row, int8_t l, int8_t r) {
	auto w = rem;
	rem.covl |= cc.cache_cov_l[row][l];
	rem.covr |= cc.cache_cov_r[row][r];
	return !(w.covl == rem.covl && w.covr == rem.covr);
}

struct Seen {
	int k;
	char seen[SZ][SZ][1<<10];
	Seen(int k):k(k) {
		assert(k<6);
		memset(seen, 0, sizeof(seen));
	}
	char &at(const P &p, const REM &rem) {
		assert(p.x < SZ && p.y < SZ && rem.covl < (1<<k) && rem.covr < (1<<k));
		int covidx = int(rem.covl) + (int(rem.covr) << k);
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
		int16_t ndist = int16_t(q.dist+1);
		if (q.p.y+k-1 >= mxy && (q.rem.covl & q.rem.covr) == cc.all_cov) {
			ans = q.dist;
			break;
		}
		if ((q.rem.covl & q.rem.covr) != cc.all_cov) {
			REM nrl(q.rem), nrr(q.rem);
			P lp { int8_t(q.p.x-1), q.p.y};
			P rp { int8_t(q.p.x+1), q.p.y};
			if (lp.x >= 0) {
				upd_rows_rem(nrl, cc, lp.y, lp.x, lp.x+k-1);
				auto &s = seen.at(lp, nrl);
				if (!s) {
					s = true;
					qq.push(Q { ndist, lp, nrl});
				}
			}
			if (rp.x+k <= SZ) {
				upd_rows_rem(nrr, cc, rp.y, rp.x, rp.x+k-1);
				auto &s = seen.at(rp, nrr);
				if (!s) {
					s = true;
					qq.push(Q { ndist, rp, nrr});
				}
			}
		}
		if (q.rem.covl & q.rem.covr & 1 == 1 && q.p.y+k <= mxy) {
			// done with row, can go up
			P up { q.p.x, int8_t(q.p.y+1)};
			REM nr(q.rem);
			nr.covl >>= 1;
			nr.covr >>= 1;
			upd_rows_rem(nr, cc, up.y, up.x, up.x+k-1);
			auto &s = seen.at(up, nr);
			if (!s) {
				s = true;
				qq.push(Q { ndist, up, nr});
			}
		}
	}
	assert(ans >= 0 && "there must be a solution");
	printf("%d\n", ans);
	return 0;
}
