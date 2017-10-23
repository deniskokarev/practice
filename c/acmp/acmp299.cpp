/* ACMP 299 */
#include <cstdio>
#include <cassert>
#include <algorithm>

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

int main(int argc, char **argv) {
	int a, b;
	assert(scanf("%d:%d", &a, &b) == 2);
	int n = std::min(a, b);
	int m = std::max(a, b);
	/* paths on the rectangular grid upto 24x24 */
	uint64_t ans = 0;
	if (n>24) {
		/* after reaching 24x24 we can walk with only 2 variants per score point */
		ans = choose(24+24, 24);
		ans *= (1ULL << (n-24));
	} else {
		if (m>24) {
			ans = choose(n+24, n);
		} else {
			// technically nobody wins
			ans = choose(n+m, n);
		}
	}
	printf("%llu\n", (unsigned long long)ans);
	return 0;
}
