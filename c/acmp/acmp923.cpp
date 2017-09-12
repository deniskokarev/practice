/* ACMP 923 */
#include <iostream>
#include <unordered_map>

using namespace std;

struct Rem {
	unordered_map<uint64_t, uint64_t> rr;
	uint64_t operator()(uint64_t n) {
		auto &r = rr[n];
		if (!r) {
			if (n == 3) {
				r = 1;
			} else if (n < 3) {
				r = 0;
			} else if ((n&1) == 0) {
				r = 2*operator()(n/2);
			} else {
				r = operator()(n/2)+operator()(n-n/2);
			}
			r++;
		}
		return r-1;
	}
};

int main(int argc, char **argv) {
	Rem rem;
	uint64_t n;
	cin >> n;
	cout << rem(n) << endl;
	return 0;
}
