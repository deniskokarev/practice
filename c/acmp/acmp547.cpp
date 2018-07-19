#include <iostream>
#include <vector>
/* ACMP 547 */
using namespace std;

int main(int argc, char **argv) {
	unsigned d;
	cin >> d;
	vector<char> ff(d*10+1); // need to stay under 16M
	unsigned step = 1;
	unsigned n = 1;
	while (n && !ff[n]) {
		ff[n] = 1;
		n %= d;
		n *= 10;
		step++;
	}
	unsigned a1, a2;
	if (n == 0) {
		a1 = step-2;
		a2 = 1;
	} else {
		unsigned fnd = n;
		unsigned end_step = step;
		n = 1;
		step = 1;
		while (n != fnd) {
			n %= d;
			n *= 10;
			step++;
		}
		a1 = step-2;
		a2 = end_step-step;
	}
	cout << a1 << ' ' << a2 << endl;
	return 0;
}
