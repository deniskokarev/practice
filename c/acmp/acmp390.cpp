/* ACMP 390 */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct P {
	int x, y;
	int cross(const P &b) const {
		return x*b.y-y*b.x;
	}
	P operator-(const P&b) const {
		P c {x, y};
		c.x -= b.x;
		c.y -= b.y;
		return c;
	}
	double len() const {
		return sqrt(x*x+y*y);
	}
};

int main(int argc, char **argv) {
	P pp[3];
	P c;
	for (auto &p:pp)
		cin >> p.x >> p.y;
	cin >> c.x >> c.y;
	double mn = 1e17;
	for (int i=0; i<2; i++) {
		int np = (i+1)%3;
		double s2 = fabs((pp[i]-c).cross(pp[np]-c));
		double h = s2/(pp[np]-pp[i]).len();
		mn = min(mn, h);
	}
	cout << setprecision(9);
	cout << mn << endl;
	return 0;
}
