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

int sign(int64_t n) {
	return (n>0)?+1:(n<0)?-1:0;
}

int64_t isqrt(int64_t value) {  
	return static_cast<int64_t>(sqrt(static_cast<double>(value)));  
} 

int main(int argc, char **argv) {
	P aa[2];
	cin >> aa[0].x >> aa[0].y >> aa[1].x >> aa[1].y;
	if (aa[0].len2() > aa[1].len2())
		swap(aa[0], aa[1]);
	P va = {aa[1].x-aa[0].x, aa[1].y-aa[0].y};
	int64_t len2 = va.len2();
	// find normal vector scaled up to |len2|
	P nr = {
		va.y*(aa[0].cross(va)),
		-va.x*(aa[0].cross(va))
	};
	// sq distances
	int64_t dn = isqrt(nr.len2())/len2;
	int64_t d[2] = {
		isqrt(aa[0].len2()),
		isqrt(aa[1].len2())
	};
	cerr << "d0: " << d[0] << " d1: " << d[1] << " dn: " << dn << endl;
	int cnt;
	if (sign(nr.cross(aa[0])) * sign(nr.cross(aa[1])) >= 0 && va.len2() <= aa[1].len2()) {
		cerr << "same side" << endl;
		cnt = d[1] - d[0];
		if (d[0]*d[0] == aa[0].len2())
			cnt++; // d[0] is precisely on the circle
	} else {
		cerr << "opposite sides" << endl;
		cnt = (d[0]-dn) + (d[1]-dn);
		if (dn*dn*len2*len2 == nr.len2())
			cnt++; // nr is precisely on the circle
	}
	// subtract if goes via O point
	if (va.cross(aa[1]) == 0 && va.len2() >= aa[1].len2())
		cnt--;
	cout << cnt << endl;
	return 0;
}
