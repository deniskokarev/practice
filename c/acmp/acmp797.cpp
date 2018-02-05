/* ACMP 797 */
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <array>

using namespace std;

constexpr int SZ = 50;

struct P {
	int x, y;
};

struct IR {
	int8_t l, r;
	operator bool() const {
		return l != 127;
	}
};

struct REM { // rows remained
	int cnt;
	array<IR, SZ> rows;
};

struct Q {
	int dist;
	P p;
	REM rem;
	bool operator<(const Q &q) const {
		return dist > q.dist;
	}
};

// "subtract" the segment [l,r] from remaining rows row, row+1,..,row+k-1
inline void upd_rows_rem(REM &rem, const vector<vector<int>> &map, int row, int8_t l, int8_t r, int k) {
	if (r<l)
		swap(l, r);
	auto &rows = rem.rows;
	for (int i=0; i<k; i++) {
		int y = row+i;
		if (y >= SZ)
			break;
		if (rem.rows[y]) {
			if (r<rem.rows[y].l || l>rem.rows[y].r) {
				continue;
			} else if (rem.rows[y].l<l && r<rem.rows[y].r) {
				continue;
			} else if (l<=rem.rows[y].l && rem.rows[y].r<=r) {
				rows[y] = IR {127, -128};
				rem.cnt--;
			} else {
				int8_t o_l = rows[y].l;
				int8_t o_r = rows[y].r;
				rows[y] = IR {127, -128};
				if (rem.rows[y].l<=l) {
					for (int8_t x=o_l; x<l; x++)
						if (map[y][x])
							rows[y] = IR {min(rows[y].l, x), max(rows[y].r, x)};
				} else {
					for (int8_t x=r+1; x<=o_r; x++)
						if (map[y][x])
							rows[y] = IR {min(rows[y].l, x), max(rows[y].r, x)};
				}
				int cnt_now = rows[y] ? 1:0;
				rem.cnt -= 1-cnt_now;
			}
		}
	}
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	P pp[n];
	int id = 1;
	vector<vector<int>> map(SZ, vector<int>(SZ, 0)); // let's assume points may not collide
	int mxy = 0;
	for (int i=0; i<n; i++) {
		auto &p = pp[i];
		cin >> p.x >> p.y;
		p.x--, p.y--;
		map[p.y][p.x] = id++;
		mxy = max(mxy, p.y);
	}
	// left/right x for each y
	REM rem;
	fill(rem.rows.begin(), rem.rows.end(), IR {127,-128});
	for (int8_t y=0; y<SZ; y++)
		for (int8_t x=0; x<SZ; x++)
			if (map[y][x])
				rem.rows[y] = IR {min(rem.rows[y].l, x), max(rem.rows[y].r, x)};
	rem.cnt = 0;
	for (int8_t y=0; y<SZ; y++)
		if (rem.rows[y])
			rem.cnt++;
	priority_queue<Q> qq;
	upd_rows_rem(rem, map, 0, 0, k-1, k);
	qq.push(Q {0, P{0, 0}, rem});
	while (!qq.empty()) {
		const Q q = qq.top();
		if (q.rem.cnt == 0)
			break;
		qq.pop();
		if (q.rem.rows[q.p.y]) {
			if (q.p.x > q.rem.rows[q.p.y].l) {
				REM nr(q.rem);
				upd_rows_rem(nr, map, q.p.y, q.rem.rows[q.p.y].l, q.p.x+k-1, k);
				qq.push(Q { q.dist+(q.p.x-q.rem.rows[q.p.y].l), P { q.rem.rows[q.p.y].l, q.p.y}, nr});
			}
			if (q.p.x+k-1 < q.rem.rows[q.p.y].r) {
				REM nr(q.rem);
				upd_rows_rem(nr, map, q.p.y, q.p.x, q.rem.rows[q.p.y].r, k);
				qq.push(Q { q.dist+(q.rem.rows[q.p.y].r-q.p.x-k+1), P { q.rem.rows[q.p.y].r-k+1, q.p.y}, nr});
			}
		} else {
			// done with row, just up
			REM nr(q.rem);
			upd_rows_rem(nr, map, q.p.y+1, q.p.x, q.p.x+k-1, k);
			qq.push(Q { q.dist+1, P { q.p.x, q.p.y+1}, nr});
		}
	}
	assert(!qq.empty() && "there must be a solution");
	const Q &top = qq.top();
	int over = top.p.y+k-1 - mxy;
	if (over < 0 || top.p.y == 0)
		over = 0;
	cout << top.dist-over << endl;
	return 0;
}
