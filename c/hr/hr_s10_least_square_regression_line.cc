#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>
/* https://www.hackerrank.com/challenges/s10-least-square-regression-line */
using namespace std;

int main(int argc, char **argv) {
	int n=5;
	double xx[n];
	double yy[n];
	for (int i=0; i<n; i++)
		cin >> xx[i] >> yy[i];
	double smx = accumulate(xx, xx+n, 0.0);
	double smy = accumulate(yy, yy+n, 0.0);
	double smx2 = accumulate(xx, xx+n, 0.0, [](double acc, double x){return acc+x*x;});
	double smxy = 0;
	for (int i=0; i<n; i++)
		smxy += xx[i]*yy[i];
	double k = (smxy*n - smx*smy)/(n*smx2 - smx*smx);
	double x0 = (smy - k*smx)/n;
	cout << setprecision(3) << fixed;
	cout << x0+k*80 << endl;
	return 0;
}
