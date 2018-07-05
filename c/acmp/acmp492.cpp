#include <iostream>
#include <cmath>
/* ACMP 492 problem */
using namespace std;

long double dist2(long double x, long double y, long double scale) {
	long double d2 = (x-x*scale)*(x-x*scale) + (y-y*scale)*(y-y*scale);
	return d2;
}

int main(int argc, char **argv) {
	double x0, y0;
	cin >> x0 >> y0;
	double vx, vy;
	cin >> vx >> vy;
	double v, t, d;
	cin >> v >> t >> d;
	long double x1 = x0 + vx*t;
	long double y1 = y0 + vy*t;
	long double eps = 1e-18;
	long double sf = -1e9, st = 1;
	while (sf+eps < st) {
		long double sm = (sf+st)/2;
		if (dist2(x1, y1, sm) > d*d)
			sf = sm+eps;
		else
			st = sm;
	}
	//cerr << sf << endl;
	long double dist = sqrtl(sf*sf*x1*x1+sf*sf*y1*y1);
	if (v*t >= dist)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}
