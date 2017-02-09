
#include <cassert>
#include "comb.hh"
#include <inttypes.h>

/**
 * Common combinatorics functions
 */

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

/**
 * LCM(a, b) - least common multiple
 */
uint64_t lcm(uint64_t a, uint64_t b) {
	return a * (b / gcd(a, b));
}
	
/**
 * Binomial coefficient (choose n, k)
 */
uint64_t choose(int n, int k) {
	assert(k <= n);
	uint64_t res = 1;
	for (uint64_t i=n,j=1; j<=k; i--,j++) {
		res *= i;
		res /= j;
		assert(res > 0);	// 64bit overflow
	}
	return res;
}
	
/**
 * factorial n!
 */
uint64_t fact(int n) {
	assert(n < 21);	// 64bit overflow with n>=21
	uint64_t res = 1;
	while (n>1)
		res *= n--;
	return res;
}

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(uint64_t n, uint64_t p[]) {
	assert(n > 1);
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
