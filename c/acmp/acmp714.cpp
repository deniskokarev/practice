/* ACMP 714 */
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <set>

using namespace std;

/*
#!/usr/bin/env python
#
# I'm too old for doing math by hand
#
from sympy import *
from sympy.utilities.codegen import codegen

# in points
a_x = Symbol('p[0].x', const=True)
a_y = Symbol('p[0].y', const=True)
b_x = Symbol('p[1].x', const=True)
b_y = Symbol('p[1].y', const=True)
# out points
c_x = Symbol('p[2].x', const=True)
c_y = Symbol('p[2].y', const=True)
d_x = Symbol('p[3].x', const=True)
d_y = Symbol('p[3].y', const=True)
# center, radius and distance to road
x = Symbol('x')
y = Symbol('y')
r1 = Symbol('r1')
r2 = Symbol('r2')

eq22_1 = (a_x - x)**2 + (a_y - y)**2 - r1**2
eq22_2 = (b_x - x)**2 + (b_y - y)**2 - r1**2
eq22_3 = (c_x - x)**2 + (c_y - y)**2 - r2**2
eq22_4 = (d_x - x)**2 + (d_y - y)**2 - r2**2

sol1 = solve([(eq22_1-eq22_2), (eq22_3-eq22_4)], x, y, dict=True)
d = denom(sol1[0][x])
xn = numer(sol1[0][x])
yn = numer(sol1[0][y])

[(c_name, c_code), (h_name, c_header)] = codegen(("d", d), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("xn", xn), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("yn", yn), "C99")
print c_code

#
# regular center of the cicle around 3 points
#
eq1 = (a_x - x)**2 + (a_y - y)**2 - r2
eq2 = (b_x - x)**2 + (b_y - y)**2 - r2
eq3 = (c_x - x)**2 + (c_y - y)**2 - r2

sol = solve([eq1-eq2, eq2-eq3], x, y)

d = denom(sol[x])
xn = numer(sol[x])
yn = numer(sol[y])

[(c_name, c_code), (h_name, c_header)] = codegen(("d", d), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("x", xn), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("y", yn), "C99")
print c_code

*/

struct P {
	int64_t x, y;
	bool operator<(const P &b) const {
		return x<b.x || (x==b.x && y<b.y);
	}
};

struct Q {
	int64_t n, d;
	Q():n(0),d(1){}
	Q(int64_t _n, int64_t _d):n(_n),d(_d) {
		if (d<0) {
			d *= -1;
			n *= -1;
		}
	}
	bool operator==(const Q &b) const {
		return n*b.d == b.n*d;
	}
	bool operator!=(const Q &b) const {
		return n*b.d != b.n*d;
	}
	bool operator<(const Q &b) const {
		return n*b.d < b.n*d;
	}
	operator long double() const {
		return ((long double)n)/d;
	}
};

inline int64_t pow(int64_t b, int p) {
	assert(p==2);
	return b*b;
}

// p[0],p[1],p[2] on same circle
bool circle_3(Q &x, Q &y, const P p[4]) {
	int64_t d = 2*(p[0].x - p[1].x)*(p[1].y - p[2].y) - 2*(p[0].y - p[1].y)*(p[1].x - p[2].x);
	if (d == 0) {
		return false;
	} else {
		int64_t xn = -(p[0].y - p[1].y)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) + (p[1].y - p[2].y)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		int64_t yn = (p[0].x - p[1].x)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) - (p[1].x - p[2].x)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		x = Q {xn, d};
		y = Q {yn, d};
		return true;
	}
}

// p[0],p[1],p[2] on same circle
// p[3] on another with same center
bool circle_3_1(Q &x, Q &y, Q &rl2, Q &rh2, const P p[4]) {
	int64_t d = 2*(p[0].x - p[1].x)*(p[1].y - p[2].y) - 2*(p[0].y - p[1].y)*(p[1].x - p[2].x);
	if (d == 0) {
		return false;
	} else {
		int64_t xn = -(p[0].y - p[1].y)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) + (p[1].y - p[2].y)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		int64_t yn = (p[0].x - p[1].x)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) - (p[1].x - p[2].x)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		x = Q {xn, d};
		y = Q {yn, d};
		rl2 = Q {pow(p[0].x*d-xn, 2) + pow(p[0].y*d-yn, 2), d*d};
		rh2 = Q {pow(p[3].x*d-xn, 2) + pow(p[3].y*d-yn, 2), d*d};
#if 0
		for (int i=0; i<4; i++)
			cerr << "pp[" << i << "]: (" << p[i].x << ", " << p[i].y << ")" << endl;
		long double lx, ly, lrl2, lrh2;
		lx = xn/d; ly = yn/d; lrl2 = rl2; lrh2 = rh2;
		cerr << "3_1 x: " << x << " y: " << y << " r: " << (sqrtl(lrl2)+sqrtl(lrh2))/2 << endl;
#endif
		if (rh2<rl2)
			swap(rh2,rl2);
		return true;
	}
}

// p[0],p[1] on one circle
// p[2],p[3] on another circle with same center
// rl2 - smallest circle ^ 2
// rh2 - biggest circle ^ 2
bool circle_2_2(Q &x, Q &y, Q &rl2, Q &rh2, const P p[4]) {
	int64_t d = 2*(p[0].x - p[1].x)*(p[2].y - p[3].y) - 2*(p[0].y - p[1].y)*(p[2].x - p[3].x);
	if (d == 0) {
		return false;
	} else {
		int64_t xn = -(p[0].y - p[1].y)*(pow(p[2].x, 2) + pow(p[2].y, 2) - pow(p[3].x, 2) - pow(p[3].y, 2)) + (p[2].y - p[3].y)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		int64_t yn = (p[0].x - p[1].x)*(pow(p[2].x, 2) + pow(p[2].y, 2) - pow(p[3].x, 2) - pow(p[3].y, 2)) - (p[2].x - p[3].x)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
		x = Q {xn, d};
		y = Q {yn, d};
		rl2 = Q {pow(p[0].x*d-xn, 2) + pow(p[0].y*d-yn, 2), d*d};
		rh2 = Q {pow(p[2].x*d-xn, 2) + pow(p[2].y*d-yn, 2), d*d};
#if 0
		long double lx, ly, lrl2, lrh2;
		lx = xn/d; ly = yn/d; lrl2 = rl2; lrh2 = rh2;
		cerr << "2_2 x: " << x << " y: " << y << " r: " << (sqrtl(lrl2)+sqrtl(lrh2))/2 << endl;
#endif
		if (rh2<rl2)
			swap(rh2,rl2);
		return true;
	}
}

bool circle_line(Q &x, Q &y, Q &rl2, Q &rh2, const P p[4]) {
	int64_t xn=0, yn=0;
	for (int i=0; i<4; i++) {
		xn += p[i].x;
		yn += p[i].y;
	}
	x = Q(xn, 4);
	y = Q(yn, 4);
	int64_t r2[4];
	for (int i=0; i<4; i++)
		r2[i] = pow(xn-p[i].x*4, 2)+pow(yn-p[i].y*4, 2);
	sort(r2, r2+4);
	rl2 = Q(r2[0], 16);
	rh2 = Q(r2[3], 16);
	if (rh2<rl2)
		swap(rh2,rl2);
	return true;
}

int main(int argc, char **argv) {
	P pp[4];
	for (auto &p:pp)
		cin >> p.x >> p.y;
	//for (int i=0; i<4; i++)
	//	cerr << "pp[" << i << "]: (" << pp[i].x << ", " << pp[i].y << ")" << endl;
	Q cx, cy;
	bool can_circle = false;
	circle_3(cx, cy, pp); // as per requirement always true
	P psel[3];
	can_circle = true;
	for (int i=0; i<4; i++) {
		copy(pp, pp+i, psel);
		copy(pp+i+1, pp+4, psel+i);
		Q x, y;
		if (!circle_3(x, y, psel) || x != cx || y != cy)
			can_circle = false;
	}
	if (can_circle) {
		cout << "Infinity" << endl;
		long double x = cx;
		long double y = cy;
		cout << fixed << setprecision(7) << x << " " << y << " 0" << endl;
	} else {
		set<tuple<Q,Q,Q,Q>> res; //x,y,r*scale
		for (int i=0; i<2*3*4; i++) {
			Q x, y, rl2, rh2;
			//for (int i=0; i<4; i++)
			//	cerr << "pp[" << i << "]: (" << pp[i].x << ", " << pp[i].y << ")" << endl;
			long double lx, ly, lrl2, lrh2;
			if (circle_3_1(x, y, rl2, rh2, pp)) {
				res.insert(make_tuple(x, y, rl2, rh2));
				//lx = x; ly = y;	lrl2 = rl2; lrh2 = rh2;
				//cerr << "x: " << lx << " y: " << y << " r: " << (sqrtl(lrl2)+sqrtl(lrh2))/2 << endl;
			}
			if (circle_2_2(x, y, rl2, rh2, pp)) {
				res.insert(make_tuple(x, y, rl2, rh2));
				//lx = x; ly = y;	lrl2 = rl2; lrh2 = rh2;
				//cerr << "x: " << lx << " y: " << y << " r: " << (sqrtl(lrl2)+sqrtl(lrh2))/2 << endl;
			}
			next_permutation(pp, pp+4);
		}
		if (res.size() > 0) {
			tuple<Q,Q,Q,Q> mn;
			long double rmn = INT_MAX;
			for (auto &t:res) {
				long double rl2 = get<2>(t);
				long double rh2 = get<3>(t);
				long double r = (sqrtl(rh2)+sqrtl(rl2))/2;
#if 0
				Q x = get<0>(t);
				Q y = get<1>(t);
				cerr << "x: " << x.n << "/" << x.d << " y: " << y.n << "/" << y.d << " r: " << r << endl;
#endif
				if (r<rmn) {
					rmn = r;
					mn = t;
				}
			}
			long double x = get<0>(mn);
			long double y = get<1>(mn);
			cout << res.size() << endl;
			cout << fixed << setprecision(7) << x << " " << y << " " << rmn << endl;
		} else {
			assert(false);
			// we know they must be symmetrical on a line (as per the problem definition)
			Q cx, cy, crl2, crh2;
			circle_line(cx, cy, crl2, crh2, pp);
			long double x = cx;
			long double y = cy;
			long double lrl2 = crl2;
			long double lrh2 = crh2;
			assert(lrh2>0 && lrl2>0);
			long double r = sqrtl(lrh2)+sqrtl(lrl2);
			cout << 1 << endl;
			cout << fixed << setprecision(7) << x << " " << y << " " << r/2 << endl;
		}
	}
	return 0;
}
