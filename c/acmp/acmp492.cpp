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
	int64_t dt2 = x1*x1+y1*y1;
	bool ans;
	if (dt2 >= d*d)
		ans = ((d+v*t)*(d+v*t) >= dt2);
	else
		ans = ((d-v*t)*(d-v*t) <= dt2) || (v*t>d);
	cout << (ans?"YES":"NO") << endl;
	return 0;
}
