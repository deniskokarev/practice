#include <iostream>
#include <vector>
/* ACMP 547 */
using namespace std;

int main(int argc, char **argv) {
	int d;
	cin >> d;
	vector<uint8_t> ff(10000001, 0);
	int step = 0;
	int n = 1;
	while (n < d) {
		n *= 10;
		step++;
	}
	while (n > 0 && ff[n] == 0) {
		ff[n] = step;
		n %= d;
		n *= 10;
		step++;
	}
	int a1, a2;
	if (n == 0) {
		a1 = step-1;
		a2 = step-1;
	} else {
		a1 = ff[n]-1;
		a2 = step-ff[n];
	}
	cout << a1 << ' ' << a2 << endl;
	return 0;
}
