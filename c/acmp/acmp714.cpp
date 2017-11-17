/* ACMP 714 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <set>

using namespace std;

using DOUBLE = long double;

/*
#!/usr/bin/env python
#
# I'm too old for doing math by hand
#
from sympy import *
from sympy.utilities.codegen import codegen

# given points
a_x = Symbol('p[0].x', const=True)
a_y = Symbol('p[0].y', const=True)
b_x = Symbol('p[1].x', const=True)
b_y = Symbol('p[1].y', const=True)
c_x = Symbol('p[2].x', const=True)
c_y = Symbol('p[2].y', const=True)
d_x = Symbol('p[3].x', const=True)
d_y = Symbol('p[3].y', const=True)
# side of the center to point relative to road
s1 = Symbol('s[0]', const=True)
s2 = Symbol('s[1]', const=True)
s3 = Symbol('s[2]', const=True)
s4 = Symbol('s[3]', const=True)
# center, radius and distance to road
x = Symbol('x')
y = Symbol('y')
r = Symbol('r')
d = Symbol('d')
eq1 = (a_x - x)**2 + (a_y - y)**2 - r**2 - d**2 - s1*2*r*d
eq2 = (b_x - x)**2 + (b_y - y)**2 - r**2 - d**2 - s2*2*r*d
eq3 = (c_x - x)**2 + (c_y - y)**2 - r**2 - d**2 - s3*2*r*d
eq4 = (d_x - x)**2 + (d_y - y)**2 - r**2 - d**2 - s4*2*r*d

# substituting r*d with rd for simplicity and solving
rd = Symbol('rd')
sol1 = solve([(eq1-eq2).subs(r*d, rd), (eq2-eq3).subs(r*d, rd), (eq3-eq4).subs(r*d, rd)], x, y, rd, dict=True)

# c1 = (a_x - x)**2 + (a_y - y)**2 - s1*2*r*d
# c1 = (b_x - x)**2 + (b_y - y)**2 - s2*2*r*d

c1 = Symbol('c1', const=True)
c2 = Symbol('c2', const=True)
r2 = Symbol('r2')
d2 = Symbol('d2')
eeq1 = c1 - r2 - d2
eeq2 = c2 - r2 - d2
sol2 = solve([eeq1, eeq2], r2, d2, dict=True)

[(c_name, c_code), (h_name, c_header)] = codegen(("x", sol1[0][x]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("y", sol1[0][y]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("rd", sol1[0][rd]), "C99")
print c_code

c1 = (a_x - x)**2 + (a_y - y)**2 - s1*2*rd
[(c_name, c_code), (h_name, c_header)] = codegen(("c1", c1), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("r1", sol2[0][r]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("r2", sol2[1][r]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("r3", sol2[2][r]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("r4", sol2[3][r]), "C99")
print c_code

[(c_name, c_code), (h_name, c_header)] = codegen(("d1", sol2[0][d]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("d2", sol2[1][d]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("d3", sol2[2][d]), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("d4", sol2[3][d]), "C99")
print c_code

#
# regular center of the cicle around 3 points
#
eq1 = (a_x - x)**2 + (a_y - y)**2 - r**2
eq2 = (b_x - x)**2 + (b_y - y)**2 - r**2
eq3 = (c_x - x)**2 + (c_y - y)**2 - r**2

sol = solve([eq1-eq2, eq2-eq3], x, y)

det = denom(sol[x])
x_num = numer(sol[x])
y_num = numer(sol[y])

[(c_name, c_code), (h_name, c_header)] = codegen(("d", det), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("x", x_num), "C99")
print c_code
[(c_name, c_code), (h_name, c_header)] = codegen(("y", y_num), "C99")
print c_code

*/

struct P {
	DOUBLE x, y;
};

inline DOUBLE pow(DOUBLE b, int p) {
	assert(p==2);
	return b*b;
}

void circle(int64_t &x, int64_t &y, int64_t &d, const P *p) {
	d = 2*(p[0].x - p[1].x)*(p[1].y - p[2].y) - 2*(p[0].y - p[1].y)*(p[1].x - p[2].x);
	x = -(p[0].y - p[1].y)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) + (p[1].y - p[2].y)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
	y = (p[0].x - p[1].x)*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) - (p[1].x - p[2].x)*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2));
}

constexpr long double scale = 1e7;

void find_xyrd(set<tuple<int64_t,int64_t,int64_t>> &rc, const P *p, const long double *s) {
	int64_t d = ((p[0].x - p[1].x)*(p[1].y - p[2].y)*(s[2] - s[3]) - (p[0].x - p[1].x)*(p[2].y - p[3].y)*(s[1] - s[2]) - (p[0].y - p[1].y)*(p[1].x - p[2].x)*(s[2] - s[3]) + (p[0].y - p[1].y)*(p[2].x - p[3].x)*(s[1] - s[2]) + (p[1].x - p[2].x)*(p[2].y - p[3].y)*(s[0] - s[1]) - (p[1].y - p[2].y)*(p[2].x - p[3].x)*(s[0] - s[1]));
	if (d == 0)
		return;
	DOUBLE x = ((1.0L/2.0L)*((p[0].y - p[1].y)*(s[1] - s[2]) - (p[1].y - p[2].y)*(s[0] - s[1]))*(pow(p[2].x, 2) + pow(p[2].y, 2) - pow(p[3].x, 2) - pow(p[3].y, 2)) - 1.0L/2.0L*((p[0].y - p[1].y)*(s[2] - s[3]) - (p[2].y - p[3].y)*(s[0] - s[1]))*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) + (1.0L/2.0L)*((p[1].y - p[2].y)*(s[2] - s[3]) - (p[2].y - p[3].y)*(s[1] - s[2]))*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2)))/((p[0].x - p[1].x)*(p[1].y - p[2].y)*(s[2] - s[3]) - (p[0].x - p[1].x)*(p[2].y - p[3].y)*(s[1] - s[2]) - (p[0].y - p[1].y)*(p[1].x - p[2].x)*(s[2] - s[3]) + (p[0].y - p[1].y)*(p[2].x - p[3].x)*(s[1] - s[2]) + (p[1].x - p[2].x)*(p[2].y - p[3].y)*(s[0] - s[1]) - (p[1].y - p[2].y)*(p[2].x - p[3].x)*(s[0] - s[1]));
	DOUBLE y = (-1.0L/2.0L*((p[0].x - p[1].x)*(s[1] - s[2]) - (p[1].x - p[2].x)*(s[0] - s[1]))*(pow(p[2].x, 2) + pow(p[2].y, 2) - pow(p[3].x, 2) - pow(p[3].y, 2)) + (1.0L/2.0L)*((p[0].x - p[1].x)*(s[2] - s[3]) - (p[2].x - p[3].x)*(s[0] - s[1]))*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) - 1.0L/2.0L*((p[1].x - p[2].x)*(s[2] - s[3]) - (p[2].x - p[3].x)*(s[1] - s[2]))*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2)))/((p[0].x - p[1].x)*(p[1].y - p[2].y)*(s[2] - s[3]) - (p[0].x - p[1].x)*(p[2].y - p[3].y)*(s[1] - s[2]) - (p[0].y - p[1].y)*(p[1].x - p[2].x)*(s[2] - s[3]) + (p[0].y - p[1].y)*(p[2].x - p[3].x)*(s[1] - s[2]) + (p[1].x - p[2].x)*(p[2].y - p[3].y)*(s[0] - s[1]) - (p[1].y - p[2].y)*(p[2].x - p[3].x)*(s[0] - s[1]));
	DOUBLE rd = ((1.0L/2.0L)*((p[0].x - p[1].x)*(p[1].y - p[2].y) - (p[0].y - p[1].y)*(p[1].x - p[2].x))*(pow(p[2].x, 2) + pow(p[2].y, 2) - pow(p[3].x, 2) - pow(p[3].y, 2)) - 1.0L/2.0L*((p[0].x - p[1].x)*(p[2].y - p[3].y) - (p[0].y - p[1].y)*(p[2].x - p[3].x))*(pow(p[1].x, 2) + pow(p[1].y, 2) - pow(p[2].x, 2) - pow(p[2].y, 2)) + (1.0L/2.0L)*((p[1].x - p[2].x)*(p[2].y - p[3].y) - (p[1].y - p[2].y)*(p[2].x - p[3].x))*(pow(p[0].x, 2) + pow(p[0].y, 2) - pow(p[1].x, 2) - pow(p[1].y, 2)))/((p[0].x - p[1].x)*(p[1].y - p[2].y)*(s[2] - s[3]) - (p[0].x - p[1].x)*(p[2].y - p[3].y)*(s[1] - s[2]) - (p[0].y - p[1].y)*(p[1].x - p[2].x)*(s[2] - s[3]) + (p[0].y - p[1].y)*(p[2].x - p[3].x)*(s[1] - s[2]) + (p[1].x - p[2].x)*(p[2].y - p[3].y)*(s[0] - s[1]) - (p[1].y - p[2].y)*(p[2].x - p[3].x)*(s[0] - s[1]));
	DOUBLE c1 = -2*rd*s[0] + pow(p[0].x - x, 2) + pow(p[0].y - y, 2);;
	DOUBLE ar[4] = {
		-sqrtl((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))*((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))/rd,
		sqrtl((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))*((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))/rd,
		-((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))*sqrtl((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))/rd,
		((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))*sqrtl((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))/rd
	};
	DOUBLE ad[4] = {
		-sqrtl((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2))),
		sqrtl((1.0L/2.0L)*c1 - 1.0L/2.0L*sqrtl(pow(c1, 2) - 4*pow(rd, 2))),
		-sqrtl((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2))),
		-sqrtl((1.0L/2.0L)*c1 + (1.0L/2.0L)*sqrtl(pow(c1, 2) - 4*pow(rd, 2)))
	};
	for (int i=0; i<4; i++) {
		//cerr << "ar[" << i << "]= " << ar[i] << endl;
		if (ar[i] > 0 && ad[i] > 0 && ar[i] > ad[i])
			rc.insert(make_tuple(ar[i]*scale,x*scale,y*scale));
	}
}

int main(int argc, char **argv) {
	P pp[4];
	for (auto &p:pp)
		cin >> p.x >> p.y;
	DOUBLE s[4];
	DOUBLE mnr = INT_MAX;
	DOUBLE mnx = 0, mny = 0;
	DOUBLE det;
	bool can_circle = false;
	int64_t cx, cy, cdet;
	circle(cx, cy, cdet, pp);
	//cerr << "x: " << cx << " cy: " << cy << " det: " << cdet << endl;
	if (cdet != 0) {
		P psel[3];
		can_circle = true;
		for (int i=0; i<2; i++) {
			for (int j=i+1; j<3; j++) {
				for (int k=j+1; k<4; k++) {
					psel[0] = pp[i];
					psel[1] = pp[j];
					psel[2] = pp[k];
					int64_t x, y, d;
					circle(x, y, d, psel);
					//cerr << "x: " << x << " cy: " << y << " det: " << d << endl;
					if (x*cdet != cx*d || y*cdet != cy*d)
						can_circle = false;
				}
			}
		}
	}
	if (can_circle) {
		cout << "Infinity" << endl;
		mnx = cx;
		mny = cy;
		det = cdet;
		cout << fixed << setprecision(6) << mnx/det << " " << mny/det << " 0.0" << endl;
	} else {
		set<tuple<int64_t,int64_t,int64_t>> res;
		for (int pw=1; pw<(1<<4)-1; pw++) {
			for (int i=0; i<4; i++)
				if (pw & (1<<i))
					s[i] = +1;
				else
					s[i] = -1;
			find_xyrd(res, pp, s);
		}
		for (auto a:res) {
			mnr = DOUBLE(get<0>(a))/scale;
			mnx = DOUBLE(get<1>(a))/scale;
			mny = DOUBLE(get<2>(a))/scale;
			break;
		}
		cout << res.size() << endl;
		cout << fixed << setprecision(6) << mnx << " " << mny << " " << mnr << endl;
	}
	return 0;
}
