/* ACMP 797 */
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <array>
#include <algorithm>

using namespace std;

constexpr int SZ = 50;

struct P {
	int x, y;
};

struct IR {
	int8_t l, r;
	operator bool() const {
		return l != INT8_MAX;
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
static void upd_rows_rem(REM &rem, const vector<vector<int>> &map, int row, int8_t l, int8_t r, int k) {
	if (r<l)
		swap(l, r);
	auto &rows = rem.rows;
	for (int i=0; i<k; i++) {
		int y = row+i;
		if (y >= SZ)
			break;
		if (rows[y]) {
			struct E {
				int8_t e;
				int8_t v;
				bool operator<(const E &b) const {
					return e<b.e;
				}
			} ends[4] = {{rows[y].l, +1}, {int8_t(rows[y].r+1), -1}, {l, -1}, {int8_t(r+1), +1}};
			sort(ends, ends+4);
			struct {
				int8_t l, r;
				int8_t v;
			} ir[3] = {{ends[0].e, ends[1].e, ends[0].v}, {ends[1].e, ends[2].e, ends[1].v}, {ends[2].e, ends[3].e, ends[2].v}};
			ir[1].v += ir[0].v;
			ir[2].v += ir[1].v;
			int8_t mne = INT8_MAX, mxe = INT8_MIN;
			for (int i=0; i<3; i++) {
				if (ir[i].l < ir[i].r && ir[i].v == 1) {
					mne = min(mne, ir[i].l);
					mxe = max(mxe, ir[i].r);
				}
			}
			if (mne < mxe) {
				rows[y] = IR {mne, int8_t(mxe-1)};
			} else {
				rows[y] = IR {INT8_MAX, INT8_MIN};
				rem.cnt--;
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
	fill(rem.rows.begin(), rem.rows.end(), IR {INT8_MAX, INT8_MIN});
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
