#include <iostream>
#include <cassert>

/* CodeForces CF894B problem */
using namespace std;

constexpr int64_t mod = 1e9+1;

int64_t p2mod(int64_t p) {
	if (p > 1) {
		return (p2mod(p/2)*p2mod(p-p/2))%mod;
	} else if (p > 0) {
		return 2;
	} else {
		return 1;
	}
}

int main(int argc, char **argv) {
	int64_t n, m;
	cin >> n >> m;
	if (n < m)
		swap(n, m); // want n>m
	int k;
	cin >> k;
	assert(k*k == 1);
	int64_t ans = 0;
	if (k>0) {
		if (m<2) {
			ans = 1;
		} else {
			ans = (p2mod(n-1)*p2mod(m-1))%mod;
		}
	} else {
		if (m<2) {
			ans = 1;
		} else {
			ans = (p2mod(n-1)*p2mod(m-1))%mod;
		}
	}
	cout << ans << endl;
	return 0;
}
