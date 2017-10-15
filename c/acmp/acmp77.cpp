/* ACMP 77 */
#include <iostream>
#include <cassert>

using namespace std;

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

int nbits(uint64_t n) {
	int b = 0;
	for (; n>0; n>>=1,b++);
	return b;
}

int main(int argc, char **argv) {
	uint64_t n;
	int k;
	cin >> n >> k;
	int b = nbits(n);
	int b2 = nbits(n - (1ULL << (b-1))); // second hi bit
	// all smaller bit scenarios
	uint64_t s = 0;
	for (int i=k; i<b-1; i++)
		s += choose(i, k);
	// try to place remaning 0s on or after second hi bit
	if (b-b2-1 < k && b2 >= k-(b-b2-1))
		s += choose(b2, k-(b-b2-1));
	cout << s << endl;
	return 0;
}
