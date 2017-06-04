#include <iostream>
/* CodeForces CF798C problem */
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

uint64_t gcd(int64_t aa[], int n) {
	uint64_t pf[65];
	int npf = primeFactors(aa[0], pf);
	uint64_t lp = -1;
	for (int i=npf-1; i>=0; i--) {
		if (pf[i] == lp)
			continue;
		lp = pf[i];
		int j;
		for (j=1; j<n && aa[j]%lp == 0 ; j++);
		if (j == n)
			return lp;
	}
	return 1;
}

int bm(int64_t aa[], int n) {
	int s = 0;
	for (int i=0; i<n-1; i++) {
		if ((aa[i]&1) == 0 && (aa[i+1]&1) == 1) {
			s += 2;
			i++;
		} else if ((aa[i]&1) == 1 && (aa[i+1]&1) == 0) {
			s += 2;
			i++;
		} else if ((aa[i]&1) == 1 && (aa[i+1]&1) == 1) {
			s += 1;
			i++;
		}
	}
	return s;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	if (n < 2 && aa[0] < 2) {
		cout << "NO" << endl;
	} else {
		uint64_t g = gcd(aa, n);
		if (g > 1)
			cout << "YES" << endl << 0 << endl;
		else
			cout << "YES" << endl << bm(aa, n) << endl;
	}
	return 0;
}
