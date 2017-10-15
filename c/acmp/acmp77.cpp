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

uint64_t cnt(const bitset<32> nn, int k, int b) {
	uint64_t s = 0;
	if (k < b) {
		int zm = 0;
		// remove hi 1 and consider seq of 1s of diminishing length
		for (int i=k; i<b-1; i++)
			s += choose(i, k);
		// keep hi 1 and try to flip lower 1s
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
		// special case of hi 1 followed by k 0s
		if (zm == k)
			s++;
	}
	return s;
}

int main(int argc, char **argv) {
	uint32_t n;
	int k;
	cin >> n >> k;
	bitset<32> nn(n);
	int b = 0;
	for (int i=0; i<32; i++)
		if (nn[i])
			b = i+1;
	cout << cnt(nn, k, b) << endl;
	return 0;
}
