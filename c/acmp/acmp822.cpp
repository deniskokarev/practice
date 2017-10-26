/* ACMP 822 */
#include <iostream>
#include <cmath>

using namespace std;

struct V {
	int x, y;
	void operator -=(const V &v) {
		x -= v.x;
		y -= v.y;
	}
};

int main(int argc, char **argv) {
	V p[3];
	cin >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> p[2].x >> p[2].y;
	p[1] -= p[0];
	p[2] -= p[0];
	double a = fabs((p[1].x*p[2].y - p[2].x*p[1].y)/2.0);
	cout << a << endl;
	return 0;
}
