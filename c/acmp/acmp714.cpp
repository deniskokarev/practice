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

# inside points
a_x = Symbol('p[0].x', const=True)
a_y = Symbol('p[0].y', const=True)
b_x = Symbol('p[1].x', const=True)
b_y = Symbol('p[1].y', const=True)

# outside points
c_x = Symbol('p[2].x', const=True)
c_y = Symbol('p[2].y', const=True)
d_x = Symbol('p[3].x', const=True)
d_y = Symbol('p[3].y', const=True)

# center, radius and distance to road
x = Symbol('x')
y = Symbol('y')
r1 = Symbol('r1')
r2 = Symbol('r2')

# r1 is inner circle, r2 is outer - they both center at x,y
eq22_1 = (a_x - x)**2 + (a_y - y)**2 - r1**2
eq22_2 = (b_x - x)**2 + (b_y - y)**2 - r1**2
eq22_3 = (c_x - x)**2 + (c_y - y)**2 - r2**2
eq22_4 = (d_x - x)**2 + (d_y - y)**2 - r2**2

# solve
sol1 = solve([(eq22_1-eq22_2), (eq22_3-eq22_4)], x, y, dict=True)
d = denom(sol1[0][x])
xn = numer(sol1[0][x])
yn = numer(sol1[0][y])

# render answers directly into C code
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

// point
struct P {
	int64_t x, y;
	bool operator<(const P &b) const {
		return x<b.x || (x==b.x && y<b.y);
	}
};

// rational number
struct Q {
	int64_t n, d;
	Q():n(0),d(1){}
	Q(const int64_t _n, const int64_t _d):n(_n),d(_d) {
		if (d<0) {
			d = -d;
			n = -n;
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

// sympy expects pow() function when it renders code
inline int64_t pow(const int64_t b, const int p) {
	assert(p==2);
	return b*b;
}

// find center of the circle containing p[0],p[1],p[2]
bool circle_3(Q &x, Q &y, const P *p) {
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

// find center and r^2 of the circle where 3 points p[0],p[1],p[2] lay
// and suqred distance from center to p[3]
// return squared radiuses in order
bool circle_3_1(Q &x, Q &y, Q &rl2, Q &rh2, const P *p) {
	if (circle_3(x, y, p)) {
		rl2 = Q {pow(p[0].x*x.d-x.n, 2) + pow(p[0].y*y.d-y.n, 2), x.d*y.d};
		rh2 = Q {pow(p[3].x*x.d-x.n, 2) + pow(p[3].y*y.d-y.n, 2), x.d*y.d};
		if (rh2<rl2)
			swap(rh2,rl2);
		return true;
	} else {
		return false;
	}
}

// solution of eq22_1,2,3,4
// get center of two circles and squares of their radiuses
// p[0],p[1] on one circle
// p[2],p[3] on another circle with same center
// rl2 - smallest circle radius ^ 2
// rh2 - biggest circle radius ^ 2
bool circle_2_2(Q &x, Q &y, Q &rl2, Q &rh2, const P *p) {
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
		if (rh2<rl2)
			swap(rh2,rl2);
		return true;
	}
}

int main(int argc, char **argv) {
	P pp[4];
	for (auto &p:pp)
		cin >> p.x >> p.y;
	Q cx, cy;
	bool can_circle_all = true;
	circle_3(cx, cy, pp);
	P psel[3];
	for (int i=0; i<4; i++) {
		copy(pp, pp+i, psel);
		copy(pp+i+1, pp+4, psel+i);
		Q x, y;
		if (!circle_3(x, y, psel) || x != cx || y != cy)
			can_circle_all = false;
	}
	if (can_circle_all) {
		cout << "Infinity" << endl;
		long double x = cx;
		long double y = cy;
		cout << fixed << setprecision(6) << x << " " << y << " 0" << endl;
	} else {
		// NB!: tests must be too weak, as we can hash the real (rl+rh)/2 value
		// simply by storing rl^2 and rh^2
		set<tuple<Q,Q,Q,Q>> res;		//x,y,rl^2,rh^2
		for (int i=0; i<2*3*4; i++) {
			Q x, y, rl2, rh2;
			if (circle_3_1(x, y, rl2, rh2, pp))
				res.insert(make_tuple(x, y, rl2, rh2));
			if (circle_2_2(x, y, rl2, rh2, pp))
				res.insert(make_tuple(x, y, rl2, rh2));
			next_permutation(pp, pp+4); // brutforce permutation method
		}
		if (res.size() > 0) {
			Q mnx, mny;
			long double rmn = INT_MAX;
			for (auto &t:res) {
				long double r = (sqrtl(get<2>(t))+sqrtl(get<3>(t)))/2;
				if (r<rmn) {
					rmn = r;
					mnx = get<0>(t);
					mny = get<1>(t);
				}
			}
			cout << res.size() << endl;
			cout << fixed << setprecision(6) << mnx << " " << mny << " " << rmn << endl;
		} else {
			// NB!: tests must be too weak as the following symmetric singe-line scenario never triggers
			// -3 0
			// -1 0
			// 1 0
			// 3 0
			// >>> 0.0 0.0 2.0
			assert(false && "no such test case when points are symmetric on the same line");
		}
	}
	return 0;
}
