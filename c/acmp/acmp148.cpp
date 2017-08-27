#include <iostream>

using namespace std;

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

int main() {
  uint64_t a,b;
  cin >> a >> b;
  cout << gcd(a,b) << endl;
}
