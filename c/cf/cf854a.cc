#include <iostream>
/* CodeForces CF854A problem */
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

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int a, b;
	for (a=n/2; a>=1; a--) {
		b = n-a;
		if (gcd(a, b) == 1)
			break;
	}
	cout << a << ' ' << b << endl;
	return 0;
}
