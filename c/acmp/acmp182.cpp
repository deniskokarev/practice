/* ACMP 182 */
#include <iostream>

using namespace std;

struct V {
	int64_t x, y;
	void operator -=(const V &v) {
		x -= v.x;
		y -= v.y;
	}
	void operator +=(const V &v) {
		x += v.x;
		y += v.y;
	}
	V operator-(const V &b) const {
		V r(*this);
		r -= b;
		return r;
	}
	V operator+(const V &b) const {
		V r(*this);
		r += b;
		return r;
	}
};

bool ort(const V &a, const V &b) {
	return a.x*b.x+a.y*b.y == 0;
}

int main(int argc, char **argv) {
	V p[3];
	cin >> p[0].x >> p[0].y >> p[1].x >> p[1].y >> p[2].x >> p[2].y;
	for (int i=0; i<3; i++) {
		int n1 = (i+1)%3;
		int n2 = (i+2)%3;
		if (ort(p[n1]-p[i], p[n2]-p[i])) {
			V r = p[n1] + p[n2] - p[i];
			cout << r.x << ' ' << r.y << endl;
			break;
		}
	}
	return 0;
}
