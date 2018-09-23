#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
/* ROI 2015E */
using namespace std;

constexpr int MXP2 = 62;

struct R {
	int64_t rem;  // total remainder
	int64_t r[3]; // individual portion
	bool operator==(const R &b) const {
		return rem == b.rem;
	}
	bool operator<(const R &b) const {
		return rem < b.rem;
	}
};

// build all allowed remainders and get their bitmasks
static vector<R> build_all_rem() {
	vector<R> rem;
	rem.push_back(R{0, {0, 0, 0}});
	for (int i=0; i<MXP2; i++) {
		int64_t vi = 1LL<<i;
		rem.push_back(R{vi, {vi, 0, 0}});
	}
	for (int i=0; i<MXP2; i++) {
		for (int j=0; j<MXP2; j++) {
			int64_t vi = 1LL<<i;
			int64_t vj = 1LL<<j;
			rem.push_back(R{vi+vj, {vi, vj, 0}});
		}
	}
	for (int i=0; i<MXP2; i++) {
		for (int j=0; j<MXP2; j++) {
			for (int k=0; k<MXP2; k++) {
				int64_t vi = 1LL<<i;
				int64_t vj = 1LL<<j;
				int64_t vk = 1LL<<k;
				rem.push_back(R{vi+vj+vk, {vi, vj, vk}});
			}
		}
	}
	sort(rem.begin(), rem.end());
	auto sz = unique(rem.begin(), rem.end()) - rem.begin();
	rem.resize(sz);
	return rem;
}

static bool iseven(int64_t n) {
	return (n&1) == 0;
}

int main(int argc, char **argv) {
	const vector<R> rem = build_all_rem();
	int t;
	cin >> t;
	while (t--) {
		int64_t n;
		cin >> n;
		bool fnd = false;
		for (auto r:rem) {
			if (n < r.rem) {
				break;
			} else if (n == r.rem) {
				cout << r.r[0] << ' ' << r.r[1] << ' ' << r.r[2] << '\n';
				fnd = true;
				break;
			} else {
				if ((n-r.rem) % 3 != 0)
					continue;
				int64_t q = (n-r.rem)/3;
				if (!iseven(q))
					continue;
				if ((q & r.rem) != 0)
					continue;
				//cerr << q << '\n';
				cout << q + r.r[0] << ' ' << q+r.r[1] << ' ' << q+r.r[2] << '\n';
				fnd = true;
				break;
			}
		}
		assert(fnd && "must find the answer");
	}
	return 0;
}
