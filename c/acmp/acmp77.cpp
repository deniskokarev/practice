/* ACMP 77 */
#include <iostream>
#include <cassert>
#include <bitset>

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

uint64_t f(const bitset<64> nn, int k, int b) {
	uint64_t s = 0;
	if (k < b) {
		int zm = 0;
		for (int i=b-2; i>=0; i--) {
			if (nn[i]) {
				if (zm <= k && i >= k-zm-1)
					s += choose(i, k-zm-1);
				else
					break;
			} else {
				zm++;
			}
		}
		if (zm == k)
			s++;
		for (int i=k; i<b-1; i++)
			s += choose(i, k);
	}
	return s;
}

int main(int argc, char **argv) {
	uint64_t n;
	int k;
	cin >> n >> k;
	bitset<64> nn(n);
	int b = 0;
	for (int i=0; i<64; i++)
		if (nn[i])
			b = i+1;
	cout << f(nn, k, b) << endl;
	return 0;
}
