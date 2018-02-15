/* ACMP 797 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
 
using namespace std;
 
constexpr int SZ = 50;
 
struct P {
	int x, y;
};
 
struct IR { // interval
	int l, r;
	operator bool() const {
		return l != INT_MAX;
	}
	static const IR empty;
};

const IR IR::empty {INT_MAX, INT_MIN};
 
struct COV { // coverage of [current,current+k-1] rows
	uint8_t l, r; // left and right ends coverage in bitmask fashion
};
 
struct Q { // next move in queue
	int dist;
	P p;
	COV cov;
};

// left and right ends coverage for next k rows
struct CovCache {
	uint8_t cache_cov_l[SZ][SZ]; // row,x -> next_k_left_mask
	uint8_t cache_cov_r[SZ][SZ]; // row,x -> next_k_right_mask
	uint8_t all_k_mask;
	// take the [l,r] intervals for each row and build a k-next rows coverage cache
	CovCache(const IR allrows[SZ], int k) {
		all_k_mask = (uint8_t(1) << k)-1;
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
	inline bool all_covered(const COV &cov) const {
		return (cov.l & cov.r & all_k_mask) == all_k_mask;
	}
	inline bool covered_last_row(const COV &cov) const {
		return cov.l & cov.r & 1;
	}
	// cover next k rows if our cursor spans [l..r] inclusive
	inline void upd_rows_cov(COV &cov, int row, int l, int r) {
		cov.l |= cache_cov_l[row][l];
		cov.r |= cache_cov_r[row][r];
	}
	inline void mv_up(COV &cov) {
		cov.l >>= 1;
		cov.r >>= 1;
	}
};
 
struct Seen {
	int k;
	char seen[SZ][SZ][1<<10]; // you don't want to come to the same point after covering same rows
	Seen(int k):k(k),seen{{{0}}} {
		assert(k<6);
	}
	char &at(const P &p, const COV &cov) {
		assert(p.x < SZ && p.y < SZ && cov.l < (1<<k) && cov.r < (1<<k));
		int covidx = int(cov.l)+(int(cov.r)<<k);
		return seen[p.y][p.x][covidx];
	}
};

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	assert(k<6);
	int mxy = 0;
	// left/right x for each y
	IR allrows[SZ];
	fill(allrows, allrows+SZ, IR::empty);
	for (int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		mxy = max(mxy, y);
		allrows[y] = IR {min(allrows[y].l, x), max(allrows[y].r, x)};
	}
	CovCache cc(allrows, k);
	COV f_cov {0, 0};
	Seen seen(k);
	queue<Q> qq;
	cc.upd_rows_cov(f_cov, 0, 0, k-1);
	qq.push(Q {0, P{0, 0}, f_cov});
	int ans = -1;
	while (!qq.empty()) {
		const Q q = qq.front();
		qq.pop();
		if (q.p.y+k-1 >= mxy && cc.all_covered(q.cov)) {
			ans = q.dist;
			break;
		}
		if (q.p.y+k <= mxy && cc.covered_last_row(q.cov)) {
			// done with last row, can go up
			P up { q.p.x, q.p.y+1};
			COV ncov(q.cov);
			cc.mv_up(ncov);
			cc.upd_rows_cov(ncov, up.y, up.x, up.x+k-1);
			auto &s = seen.at(up, ncov);
			if (!s) {
				s = true;
				qq.push(Q { q.dist+1, up, ncov});
			}
		}
		if (!cc.all_covered(q.cov)) {
			// need to keep sweeping left/right
			COV ncovl(q.cov), ncovr(q.cov);
			P lp { q.p.x-1, q.p.y};
			P rp { q.p.x+1, q.p.y};
			if (lp.x >= 0) {
				cc.upd_rows_cov(ncovl, lp.y, lp.x, lp.x+k-1);
				auto &s = seen.at(lp, ncovl);
				if (!s) {
					s = true;
					qq.push(Q { q.dist+1, lp, ncovl});
				}
			}
			if (rp.x+k <= SZ) {
				cc.upd_rows_cov(ncovr, rp.y, rp.x, rp.x+k-1);
				auto &s = seen.at(rp, ncovr);
				if (!s) {
					s = true;
					qq.push(Q { q.dist+1, rp, ncovr});
				}
			}
		}
	}
	assert(ans >= 0 && "there must be a solution");
	cout << ans << endl;
	return 0;
}
