/* ACMP 384 */
#include <iostream>

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

using namespace std;

uint64_t mod = 1e9;

int main() {
	int i, j;
	cin >> i >> j;
	uint64_t f1, f2;
	f1=0; f2=1;
	// https://en.wikipedia.org/wiki/Fibonacci_number#Primes_and_divisibility
	for (int g=gcd(i, j); g>0; --g) {
		uint64_t f = (f1+f2)%mod;
		f1 = f2;
		f2 = f;
	}
	cout << f1 << endl;
}
