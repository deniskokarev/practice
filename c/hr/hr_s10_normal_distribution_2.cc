#include <iostream>
#include <iomanip>
#include <cmath>
/* Hackerrank https://www.hackerrank.com/challenges/s10-normal-distribution-2 */
using namespace std;

int main(int argc, char **argv) {
	double m = 70;
	double stdev = 10;
	double p60 = (1.0+erf((60-m)/stdev/sqrt(2)))/2;
	double p80 = (1.0+erf((80-m)/stdev/sqrt(2)))/2;
	cout << setprecision(2) << fixed;
	cout << (1-p80)*100 << endl;
	cout << (1-p60)*100 << endl;
	cout << p60*100 << endl;
	return 0;
}
