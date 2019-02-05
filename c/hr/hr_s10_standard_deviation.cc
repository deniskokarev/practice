#include <iostream>
#include <iomanip>
#include <cmath>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-standard-deviation */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t sm = 0;
	uint64_t sm2 = 0;
	for (int i=0; i<n; i++) {
		int a;
		cin >> a;
		sm += a;
		sm2 += uint64_t(a)*a;
	}
	double mean = (double)sm/n;
	double variance = (double)sm2/n - mean*mean;
	cout << setprecision(1) << fixed << sqrt(variance) << endl;
	return 0;
}
