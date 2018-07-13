#include <iostream>
/* ACMP 492 problem */
using namespace std;

int main(int argc, char **argv) {
	int64_t x0, y0;
	cin >> x0 >> y0;
	int64_t vx, vy;
	cin >> vx >> vy;
	int64_t v, t, d;
	cin >> v >> t >> d;
	int64_t x1 = x0+vx*t;
	int64_t y1 = y0+vy*t;
	int64_t dsp2 = d+v*t;
	dsp2 *= dsp2;
	int64_t dsm2 = d-v*t;
	dsm2 *= dsm2;
	int64_t dt2 = x1*x1+y1*y1;
	bool ans;
	if (dt2 >= d*d)
		ans = (dsp2 >= dt2);
	else
		ans = (dsm2 <= dt2);
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
