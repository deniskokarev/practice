/* ACMP 494 */ 
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

struct P {
	int64_t x, y;
	int64_t len2() const {
		return x*x + y*y;
	}
	int64_t cross(const P &b) const {
		return x*b.y - y*b.x;
	}
	void operator=(const P &b) {
		x = b.x;
		y = b.y;
	}
};

int64_t isqrt(int64_t value) {  
	return static_cast<int64_t>(sqrt(static_cast<double>(value)));  
}

int main(int argc, char **argv) {
	P aa[2];
	cin >> aa[0].x >> aa[0].y >> aa[1].x >> aa[1].y;
	// make aa[0] smaller vector
	if (aa[0].len2() > aa[1].len2())
		swap(aa[0], aa[1]);
	P va = {aa[1].x-aa[0].x, aa[1].y-aa[0].y};
	int64_t s = aa[0].cross(aa[1]);
	int64_t dn = isqrt(s*s/va.len2());
	int64_t d[2] = {
		isqrt(aa[0].len2()),
		isqrt(aa[1].len2())
	};
	//cerr << "d0: " << d[0] << " d1: " << d[1] << " dn: " << dn << endl;
	int cnt;
	if (dn*dn+va.len2() > aa[1].len2()) {
		//cerr << "opposite sides" << endl;
		cnt = (d[0]-dn) + (d[1]-dn);
		if (dn > 0 && dn*dn*va.len2() == s*s)
			cnt++; // normal is precisely on the circle != O
	} else {
		//cerr << "same side" << endl;
		cnt = d[1] - d[0];
		if (d[0]*d[0] == aa[0].len2() && aa[0].len2() > 0)
			cnt++; // d[0] is precisely on the circle != 0
	}
	cout << cnt << endl;
	return 0;
}
