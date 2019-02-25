#include <iostream>
#include <iomanip>
#include <cmath>
/* https://www.hackerrank.com/challenges/s10-the-central-limit-theorem-3 */
using namespace std;

double prob(double m, double stdev, double d) {
	double p_lo = (1.0+erf((-d)/stdev/sqrt(2)))/2;
	double p_hi = 1-p_lo;
	return p_hi - p_lo;
}

int main(int argc, char **argv) {
	int n = 100;
	double mean = 500*n;
	double stdev = 80*sqrt(n);
	double f=0, t=100000;
	const double eps = 0.000001;
	while (f+eps<t) {
		double m = (f+t)/2;
		if (prob(mean, stdev, m) < 0.95)
			f = m;
		else
			t = m;
	}
	cout << setprecision(4) << fixed;
	cout << (mean-f)/n << endl;
	cout << (mean+f)/n << endl;
	return 0;
}
