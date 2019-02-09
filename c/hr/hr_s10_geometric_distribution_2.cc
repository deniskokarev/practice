#include <iostream>
#include <iomanip>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-geometric-distribution-2 */

using namespace std;

int main(int argc, char **argv) {
	const double p = 1.0/3;
	double sm = 0;
	double r = 1;
	for (int n=0; n<5; n++) {
		sm += r * p;
		r *= (1.0-p);
	}
	cout << fixed << setprecision(3) << sm << endl;
	return 0;
}
