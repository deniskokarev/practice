#include <iostream>
#include <iomanip>
#include <cmath>
/* Hackerrank https://www.hackerrank.com/challenges/s10-normal-distribution-1 */
using namespace std;

int main(int argc, char **argv) {
	double m = 20;
	double stdev = 2;
	double p19_5 = (1.0+erf((19.5-m)/stdev/sqrt(2)))/2;
	double p20 = (1.0+erf((20-m)/stdev/sqrt(2)))/2;
	double p22 = (1.0+erf((22-m)/stdev/sqrt(2)))/2;
	cout << setprecision(3) << fixed;
	cout << p19_5 << endl;
	cout << p22-p20 << endl;
	return 0;
}
