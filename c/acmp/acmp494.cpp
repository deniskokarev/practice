/* ACMP 494 */ 
#include <iostream>
#include <algorithm>

using namespace std;

struct P {
	int64_t x, y;
	int64_t len2() const {
		return x*x + y*y;
	}
	int64_t cross(const P &b) const {
		return x*b.y - y*b.x;
	}
};

int sign(int64_t n) {
	return (n>0)?+1:(n<0)?-1:0;
}

int64_t isqrt(int64_t n) {
	int64_t xp = n;
	int64_t x = (xp+n/xp)/2;
	while (xp > x) {
		xp = x;
		x = (xp+n/xp)/2;
	}
	return x;
}

int main(int argc, char **argv) {
	P aa[2];
	cin >> aa[0].x >> aa[0].y >> aa[1].x >> aa[1].y;
	P va = {aa[1].x-aa[0].x, aa[1].y-aa[0].y};
	int64_t len2 = va.len2();
	// find normal vector scaled up to |len2|
	P nr = {
		va.y*(aa[0].x*va.y-aa[0].y*va.x),
		-va.x*(aa[0].x*va.y-aa[0].y*va.x)
	};
	// sq distances
	int64_t dn = isqrt(nr.len2()/len2/len2);
	int64_t d0 = isqrt(aa[0].len2());
	int64_t d1 = isqrt(aa[1].len2());
	//cerr << "d0: " << d0 << " d1: " << d1 << " dn: " << dn << endl;
	int cnt;
	if (sign(nr.cross(aa[0])) * sign(nr.cross(aa[1])) >= 0) {
		//cerr << "same side" << endl;
		cnt = max(d0,d1) - min(d0,d1);
	} else {
		//cerr << "opposite sides" << endl;
		cnt = (d0-dn) + (d1-dn);
		if (dn*dn*len2*len2 == nr.len2())
			cnt++; // nr is precisely on the circle
	}
	cout << cnt << endl;
	return 0;
}
