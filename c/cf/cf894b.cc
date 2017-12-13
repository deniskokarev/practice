#include <iostream>
#include <cassert>
/* CodeForces CF894B problem */
using namespace std;

constexpr uint64_t mod = 1e9+7;

uint64_t pow_mod(uint64_t b, uint64_t p) {
	if (p > 1) {
		uint64_t r = pow_mod(b, p/2);
		if ((p&1) == 0)
			return (r*r)%mod;
		else
			return (((r*r)%mod)*b)%mod;
	} else if (p > 0) {
		return b;
	} else {
		return 1;
	}
}

int main(int argc, char **argv) {
	uint64_t n, m;
	cin >> n >> m;
	int k;
	cin >> k;
	assert(k*k == 1);
	uint64_t ans = 0;
	if (k > 0) {
		// +1
		ans = pow_mod(pow_mod(2, n-1), m-1);
	} else {
		// -1
		if (((m+n)&1) == 1)
			ans = 0;
		else
			ans = pow_mod(pow_mod(2, n-1), m-1);
	}
	cout << ans << endl;
	return 0;
}
