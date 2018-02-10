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
	int8_t cnt;
	array<IR, 5> rows; // care only upto 5 next rows
	IR &operator[](int y) {
		return rows[y%5];
	}
	const IR &operator[](int y) const {
		return rows[y%5];
	}
};

struct Q {
	int dist;
	P p;
	REM rem;
	bool operator<(const Q &q) const {
		return dist > q.dist;
	}
};

// precompute segment subtractions
struct SubtractSeg {
	IR cached_res[SZ][SZ][SZ][SZ];
	SubtractSeg() {
		for (int8_t rl=0; rl<SZ; rl++) {
			for (int8_t rr=0; rr<SZ; rr++) {
				for (int8_t l=0; l<SZ; l++) {
					for (int8_t r=0; r<SZ; r++) {
						if (rr<rl || r<l) {
							cached_res[l][r][rl][rr] = {INT8_MAX, INT8_MIN};
						} else {
							struct E {
								int8_t e;
								int8_t v;
								bool operator<(const E &b) const {
									return e<b.e;
								}
							} ends[4] = {{rl, +1}, {int8_t(rr+1), -1}, {l, -1}, {int8_t(r+1), +1}};
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
							if (mne < mxe)
								cached_res[l][r][rl][rr] = IR {mne, int8_t(mxe-1)};
							else
								cached_res[l][r][rl][rr] = IR {INT8_MAX, INT8_MIN};
						}
					}
				}
			}
		}
	}
	IR sub(IR a, IR b) const {
		if (a)
			return cached_res[b.l][b.r][a.l][a.r];
		else
			return a;
	}
};

// "subtract" the segment [l,r] from remaining rows row, row+1,..,row+k-1
static void upd_rows_rem(REM &rem, const vector<vector<int>> &map, int row, int8_t l, int8_t r, int k) {
	static const SubtractSeg sseg;
	if (r<l)
		swap(l, r);
	for (int i=0; i<k; i++) {
		int y = row+i;
		if (y >= SZ)
			break;
		auto &rows_y = rem[y];
		if (rows_y) {
			rows_y = sseg.sub(rows_y, IR {l, r});
			if (!rows_y)
				rem.cnt--;
		}
	}
}

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	assert(k<6);
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
	IR allrows[SZ];
	fill(allrows, allrows+SZ, IR {INT8_MAX, INT8_MIN});
	for (int8_t y=0; y<SZ; y++)
		for (int8_t x=0; x<SZ; x++)
			if (map[y][x])
				allrows[y] = IR {min(allrows[y].l, x), max(allrows[y].r, x)};
	REM rem;
	rem.cnt = 0;
	for (int8_t y=0; y<SZ; y++)
		if (allrows[y])
			rem.cnt++;
	priority_queue<Q> qq;
	for (int y=0; y<5; y++)
		rem.rows[y] = allrows[y];
	upd_rows_rem(rem, map, 0, 0, k-1, k);
	qq.push(Q {0, P{0, 0}, rem});
	while (!qq.empty()) {
		const Q q = qq.top();
		if (q.rem.cnt == 0)
			break;
		qq.pop();
		const auto &row_y = q.rem[q.p.y];
		if (row_y) {
			if (q.p.x > row_y.l) {
				REM nr(q.rem);
				upd_rows_rem(nr, map, q.p.y, row_y.l, q.p.x+k-1, k);
				qq.push(Q { q.dist+(q.p.x-row_y.l), P { row_y.l, q.p.y}, nr});
			}
			if (q.p.x+k-1 < row_y.r) {
				REM nr(q.rem);
				upd_rows_rem(nr, map, q.p.y, q.p.x, row_y.r, k);
				qq.push(Q { q.dist+(row_y.r-q.p.x-k+1), P { row_y.r-k+1, q.p.y}, nr});
			}
		} else {
			// done with row, just up
			REM nr(q.rem);
			if (q.p.y+5 < SZ)
				nr[q.p.y] = allrows[q.p.y+5];
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
