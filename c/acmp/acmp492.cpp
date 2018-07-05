#include <iostream>
/* ACMP 492 problem */
using namespace std;

using numtype = __float128; 

numtype dist2(numtype x, numtype y, numtype scale) {
	numtype d2 = (x-x*scale)*(x-x*scale) + (y-y*scale)*(y-y*scale);
	return d2;
}
 
int main(int argc, char **argv) {
	int x0, y0;
	cin >> x0 >> y0;
	int vx, vy;
	cin >> vx >> vy;
	int v, t, d;
	cin >> v >> t >> d;
	numtype x1 = x0 + vx*t;
	numtype y1 = y0 + vy*t;
	numtype eps = 1e-17;
	numtype sf = -1e10, st = 1+eps;
	while (sf+eps < st) {
		numtype sm = (sf+st)/2;
		if (dist2(x1, y1, sm) > d*d)
			sf = sm+eps;
		else
			st = sm;
	}
	//cerr << sf << endl;
	numtype d2 = (x1*x1+y1*y1)*sf*sf;
	if (v*v*t*t >= d2)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}
