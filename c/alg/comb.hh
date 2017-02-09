#include <inttypes.h>
/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b);

/**
 * LCM(a, b) - least common multiple
 */
uint64_t lcm(uint64_t a, uint64_t b);

/**
 * Binomial coefficient (choose n, k)
 */
uint64_t choose(int n, int k);

/**
 * factorial n!
 */
uint64_t fact(int n);

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(uint64_t n, uint64_t p[]);
