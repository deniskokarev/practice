/* ACMP 822 */
#include <iostream>
#include <cmath>

using namespace std;

struct V {
	int64_t x, y;
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
	int64_t a2 = abs(p[1].x*p[2].y - p[2].x*p[1].y);
	if ((a2 & 1) == 0)
		cout << a2/2 << endl;
	else
		cout << a2/2 << ".5" << endl;
	return 0;
}
