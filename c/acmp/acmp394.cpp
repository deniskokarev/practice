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

int main() {
  uint64_t n, m;
  cin >> n >> m;
  cout << n/gcd(n,m) << endl;
  return 0;
}
