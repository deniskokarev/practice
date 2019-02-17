#include <iostream>
#include <iomanip>
#include <cmath>
/* Hackerrank https://www.hackerrank.com/challenges/s10-poisson-distribution-2 */
using namespace std;

int main(int argc, char **argv) {
	double m1 = 0.88;
	double var1 = m1;
	double m2 = 1.55;
	double var2 = m2;
	double p1 = 160.0 + 40 * (var1 + m1*m1);
	double p2 = 128.0 + 40 * (var2 + m2*m2);
	cout << setprecision(3) << fixed << p1 << endl << p2 << endl;
	return 0;
}
