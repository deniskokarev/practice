#include <iostream>
#include <iomanip>
#include <cmath>
#include <numeric>
/* https://www.hackerrank.com/challenges/s10-pearson-correlation-coefficient */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	double xx[n];
	for (auto &x:xx)
		cin >> x;
	double yy[n];
	for (auto &y:yy)
		cin >> y;
	double mx = accumulate(xx, xx+n, 0.0)/n;
	double my = accumulate(yy, yy+n, 0.0)/n;
	double vx = accumulate(xx, xx+n, 0.0, [mx](double acc, double x){return acc+(mx-x)*(mx-x);})/n;
	double vy = accumulate(yy, yy+n, 0.0, [my](double acc, double y){return acc+(my-y)*(my-y);})/n;
	double sm = 0;
	for (int i=0; i<n; i++)
		sm += (xx[i]-mx)*(yy[i]-my);
	double pc = sm/(n*sqrt(vx*vy));
	cout << setprecision(3) << fixed;
	cout << pc << endl;
	return 0;
}
