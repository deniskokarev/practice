/* ACMP 299 */
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

int min(int a, int b) {
	return (a<b)?a:b;
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

int main(int argc, char **argv) {
	int n, m;
	scanf("%d:%d", &n, &m);
	/* paths on the rectangular grid upto 24x24 */
	uint64_t ans = 0;
	if (n>24) {
		if (m>24) {
			/* then from 24x24 we can walk with only 2 variants per score point */
			ans = choose(24+24, 24);
			ans += (min(n, m)-24)*2;
		} else {
			ans = choose(m+24, m);
		}
	} else {
		if (m>24) {
			ans = choose(n+24, n);
		} else {
			// nobody wins
			ans = choose(n+m, n);
		}
	}
	printf("%llu\n", ans);
	return 0;
}
