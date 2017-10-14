/* ACMP 1014 */
#include <iostream>
#include <cassert>

using namespace std;

constexpr uint64_t mod = 1e9+9;

/**
 * factorial n!
 */
uint64_t fact(int n) {
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

/**
 * Binomial coefficient (choose n, k)
 */
uint64_t choose(int n, int k) {
	assert(k <= n);
	uint64_t res = 1;
	for (int i=n,j=1; j<=k; i--,j++) {
		res *= i;
		res /= j;
		assert(res > 0);	// 64bit overflow
	}
	return res;
}

uint64_t f(int n) {
	if (n>=2) {
		uint64_t s = fact(n-1);
		for (int i=1; i<=n-3; i++) {
			s += choose(n-1, i) * f(n-i-1) * fact(i);
			s %= mod;
		}
		return s;
	} else {
		return 0;
	}
}

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	cout << f(n) << endl;
	return 0;
}
