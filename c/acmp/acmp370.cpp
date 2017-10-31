/* ACMP 370 */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct P {
	double x, y;
	double cross(const P &b) const {
		return x*b.y - y*b.x;
	}
	void operator += (const P &b) {
		x += b.x;
		y += b.y;
	}
	void operator -= (const P &b) {
		x -= b.x;
		y -= b.y;
	}
	void operator /= (double b) {
		x /= b;
		y /= b;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	P vv[n];
	P o {0, 0};
	for (auto &v:vv) {
		cin >> v.x >> v.y;
		o += v;
	}
	o /= n;
	for (auto &v:vv)
		v -= o;
	double s = 0;
	for (int i=0; i<n; i++) {
		int j = (i+1)%n;
		s += vv[i].cross(vv[j]);
	}
	cout << fixed << setprecision(1) << fabs(s/2) << endl;
	return 0;
}
