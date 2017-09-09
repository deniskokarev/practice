/* ACMP 923 */
#include <iostream>
#include <vector>

using namespace std;

struct Rem {
	vector<uint64_t> rr;
	Rem():rr(1<<20, ULLONG_MAX) {
		for (int i=0; i<rr.size(); i++)
			rr[i] = bld_rem(i);
	}
	uint64_t bld_rem(uint64_t n) {
		if (rr[n] == ULLONG_MAX) {
			if (n == 3) {
				rr[n] = 1;
			} else if (n < 3) {
				rr[n] = 0;
			} else if ((n&1) == 0) {
				rr[n] = 2*bld_rem(n/2);
			} else {
				rr[n] = bld_rem(n/2)+bld_rem(n-n/2);
			}
		}
		return rr[n];
	}
	uint64_t operator()(uint64_t n) const {
		if (n < rr.size()) {
			return rr[n];
		} else if ((n&1) == 0) {
			return 2*operator()(n/2);
		} else {
			return operator()(n/2)+operator()(n-n/2);
		}
	}
};

int main(int argc, char **argv) {
	Rem rem;
	uint64_t n;
	cin >> n;
	cout << rem(n) << endl;
	return 0;
}
