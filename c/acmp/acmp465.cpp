/* ACMP 465 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t f1 = 1; // fib - 1
	uint64_t f2 = 1; // fib - 2
	for (int i=0; i<n; i++) {
		uint64_t f = f1+f2;
		f2 = f1;
		f1 = f;
	}
	cout << f1 << endl;
	return 0;
}
