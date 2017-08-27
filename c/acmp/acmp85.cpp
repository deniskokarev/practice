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
  int n, m;
  cin >> n >> m;
  int k = gcd(n, m);
  for (int i=0; i<k; i++)
    cout << '1';
  cout << endl;
  return 0;
}

