/* ACMP 90 */
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
	int64_t dot(const V &b) const {
		return x*b.x+y*b.y;
	}
	int64_t cross(const V &b) const {
		return x*b.y-b.x*y;
	}	
};

int main(int argc, char **argv) {
	V p;
	cin >> p.x >> p.y;
	int n;
	cin >> n;
	int out[n]; // output buffer
	int on = 0;
	for (int i=1; i<=n; i++) {
		V v[3];
		cin >> v[0].x >> v[0].y >> v[1].x >> v[1].y >> v[2].x >> v[2].y;
		int j;
		for (j=0; j<3; j++) {
			int n1 = (j+1)%3;
			int n2 = (j+2)%3;
			V s1 = v[n1]-v[j];
			V s2 = v[n2]-v[j];
			V sp = p - v[j];
			auto cr1 = s1.cross(s2);
			auto cr2 = s1.cross(sp);
			auto cr3 = sp.cross(s2);
			//cerr << "cr1: " << cr1 << " cr2: " << cr2 << " cr3: " << cr3 << endl;
			if ((cr1 > 0 && cr2 > 0 && cr3 > 0) || (cr1 < 0 && cr2 < 0 && cr3 < 0))
				continue;
			else
				break;
		}
		if (j == 3)
			out[on++] = i;
	}
	cout << on << endl;
	for (int i=0; i<on; i++)
		cout << out[i] << " ";
	cout << endl;
	return 0;
}
