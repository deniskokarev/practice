#include <iostream>
/* CodeForces CF797A problem */
using namespace std;

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(uint64_t n, uint64_t p[]) {
	int np = 0;
	for (uint64_t i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

int main(int argc, char **argv) {
	uint64_t n;
	int k;
	cin >> n >> k;
	uint64_t pf[64];
	int pfn = primeFactors(n, pf);
	if (pfn < k) {
		cout << -1;
	} else {
		int i;
		for (i=0; i<k-1; i++)
			cout << pf[i] << ' ';
		uint64_t lst = 1;
		for (; i<pfn; i++)
			lst *= pf[i];
		cout << lst;
	}
	cout << endl;
	return 0;
}
