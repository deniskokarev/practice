#include <iostream>
#include <vector>
#include <cassert>
/* ROI 2015E */

struct R {
	int64_t rem;  // total remainder
	int64_t r[3]; // individual portion
	int64_t msk;  // bitmask of r[0] | r[1] | r[2]
};

constexpr int MXP2 = 62; // upto 2^MXP2

// build all allowed remainders and get their bitmasks for upto 2^mxp2 each
static const std::vector<R> build_allrem(int mxp2) {
	std::vector<R> rem;
	rem.push_back(R{0, {0, 0, 0}, 0});
	for (int i=0; i<mxp2; i++) {
		int64_t vi = 1LL<<i;
		rem.push_back(R {vi, {0, 0, vi}, vi});
	}
	for (int i=0; i<mxp2; i++) {
		for (int j=i; j<mxp2; j++) {
			int64_t vi = 1LL<<i;
			int64_t vj = 1LL<<j;
			rem.push_back(R {vi+vj, {0, vi, vj}, vi|vj});
		}
	}
	for (int i=0; i<mxp2; i++) {
		for (int j=i; j<mxp2; j++) {
			for (int k=j; k<mxp2; k++) {
				int64_t vi = 1LL<<i;
				int64_t vj = 1LL<<j;
				int64_t vk = 1LL<<k;
				rem.push_back(R {vi+vj+vk, {vi, vj, vk}, vi|vj|vk});
			}
		}
	}
	return rem;
}

int main(int argc, char **argv) {
	auto allrem = build_allrem(MXP2);
	int t;
	std::cin >> t;
	while (t--) {
		int64_t n;
		std::cin >> n;
		// find best quotient and best remainder corresponding to it
		R *best_rem = nullptr;
		int64_t best_q = 0;
		for (auto &r:allrem) {
			if (n == r.rem && best_q == 0) {
				best_rem = &r;
			} else if (n > r.rem && (n-r.rem) % 3 == 0) {
				int64_t q = (n-r.rem)/3;
				if ((q & r.msk) == 0 && q > best_q) {
					best_rem = &r;
					best_q = q;
				}
			}
		}
		assert((best_rem != nullptr) && "must find the answer");
		std::cerr << best_q << '\n';
		std::cout << best_q + best_rem->r[0] << ' '
				  << best_q + best_rem->r[1] << ' '
				  << best_q + best_rem->r[2] << '\n';
	}
	return 0;
}
