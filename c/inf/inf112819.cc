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
	int64_t msk;  // bitmask of r[0] | r[1] | r[2]
};

// build all allowed remainders and get their bitmasks
static vector<R> build_all_rem() {
	vector<R> rem;
	rem.push_back(R{0, {0, 0, 0}, 0});
	for (int i=0; i<MXP2; i++) {
		int64_t vi = 1LL<<i;
		rem.push_back(R{vi, {0, 0, vi}, vi});
	}
	for (int i=0; i<MXP2; i++) {
		for (int j=i; j<MXP2; j++) {
			int64_t vi = 1LL<<i;
			int64_t vj = 1LL<<j;
			rem.push_back(R{vi+vj, {0, vi, vj}, vi|vj});
		}
	}
	for (int i=0; i<MXP2; i++) {
		for (int j=i; j<MXP2; j++) {
			for (int k=j; k<MXP2; k++) {
				int64_t vi = 1LL<<i;
				int64_t vj = 1LL<<j;
				int64_t vk = 1LL<<k;
				rem.push_back(R{vi+vj+vk, {vi, vj, vk}, vi|vj|vk});
			}
		}
	}
	return rem;
}

int main(int argc, char **argv) {
	const vector<R> rem = build_all_rem();
	int t;
	cin >> t;
	while (t--) {
		int64_t n;
		cin >> n;
		int fnd = -1;
		int mxq = 0;
		for (int i=0; i<rem.size(); i++) {
			auto &r = rem[i];
			if (n == r.rem && mxq == 0) {
				fnd = i;
			} else if (n > r.rem && (n-r.rem) % 3 == 0) {
				int64_t q = (n-r.rem)/3;
				if ((q&r.msk) == 0 && q > mxq) {
					fnd = i;
					mxq = q;
				}
			}
		}
		assert((fnd>=0) && "must find the answer");
		//cerr << mxq << '\n';
		cout << mxq + rem[fnd].r[0] << ' ' << mxq + rem[fnd].r[1] << ' ' << mxq + rem[fnd].r[2] << '\n';
	}
	return 0;
}
