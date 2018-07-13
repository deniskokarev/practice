#include <iostream>
/* ACMP 492 problem */
using namespace std;

int main(int argc, char **argv) {
	int x0, y0;
	cin >> x0 >> y0;
	int vx, vy;
	cin >> vx >> vy;
	int v, t, d;
	cin >> v >> t >> d;
	int x1 = x0+vx*t;
	int y1 = y0+vy*t;
	int64_t dsp2 = d+v*t;
	dsp2 *= dsp2;
	int64_t dsm2 = d-v*t;
	dsm2 *= dsm2;
	int64_t dt2 = x1*x1+y1*y1;
	if (dsp2 < dt2 || dsm2 > dt2)
		cout << "NO" << endl;
	else
		cout << "YES" << endl;
	return 0;
}
