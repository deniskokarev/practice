#include <iostream>
#include <iomanip>
/* Hackerrank stats https://www.hackerrank.com/challenges/s10-geometric-distribution-1 */

using namespace std;

int main(int argc, char **argv) {
	double p = 1.0/3;
	double r = 1;
	for (int i=0; i<4; i++)
		r *= (1.0-p);
	cout << fixed << setprecision(3) << r * p << endl;
	return 0;
}
