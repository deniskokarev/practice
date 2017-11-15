/* ACMP 931 */
#include <iostream>
#include <tuple>
#include <vector>
#include <cassert>
using namespace std;

/*
from sympy import *

p1_x = Symbol('p[i].x', const=True)
p1_y = Symbol('p[i].y', const=True)
p2_x = Symbol('p[j].x', const=True)
p2_y = Symbol('p[j].y', const=True)
p3_x = Symbol('p[k].x', const=True)
p3_y = Symbol('p[k].y', const=True)

x = Symbol('x')
y = Symbol('y')
r2 = Symbol('r_sq')

eq1 = Eq((p1_x - x)**2 + (p1_y - y)**2, r2)
eq2 = Eq((p2_x - x)**2 + (p2_y - y)**2, r2)
eq3 = Eq((p3_x - x)**2 + (p3_y - y)**2, r2)

sol = solve([eq1, eq2, eq3], x, y, r2, dict=True)

>>> sol[0][x]
(p[i].x**2*p[j].y - p[i].x**2*p[k].y + p[i].y**2*p[j].y - p[i].y**2*p[k].y - p[i].y*p[j].x**2 - p[i].y*p[j].y**2 + p[i].y*p[k].x**2 + p[i].y*p[k].y**2 + p[j].x**2*p[k].y + p[j].y**2*p[k].y - p[j].y*p[k].x**2 - p[j].y*p[k].y**2)/(2*(p[i].x*p[j].y - p[i].x*p[k].y - p[i].y*p[j].x + p[i].y*p[k].x + p[j].x*p[k].y - p[j].y*p[k].x))
>>> sol[0][y]
(-p[i].x**2*p[j].x + p[i].x**2*p[k].x + p[i].x*p[j].x**2 + p[i].x*p[j].y**2 - p[i].x*p[k].x**2 - p[i].x*p[k].y**2 - p[i].y**2*p[j].x + p[i].y**2*p[k].x - p[j].x**2*p[k].x + p[j].x*p[k].x**2 + p[j].x*p[k].y**2 - p[j].y**2*p[k].x)/(2*(p[i].x*p[j].y - p[i].x*p[k].y - p[i].y*p[j].x + p[i].y*p[k].x + p[j].x*p[k].y - p[j].y*p[k].x))
>>> sol[0][r2]
(p[i].x**2 - 2*p[i].x*p[j].x + p[i].y**2 - 2*p[i].y*p[j].y + p[j].x**2 + p[j].y**2)*(p[i].x**2 - 2*p[i].x*p[k].x + p[i].y**2 - 2*p[i].y*p[k].y + p[k].x**2 + p[k].y**2)*(p[j].x**2 - 2*p[j].x*p[k].x + p[j].y**2 - 2*p[j].y*p[k].y + p[k].x**2 + p[k].y**2)/(4*(p[i].x*p[j].y - p[i].x*p[k].y - p[i].y*p[j].x + p[i].y*p[k].x + p[j].x*p[k].y - p[j].y*p[k].x)**2)

 */

struct P {
	int64_t x, y;
};

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

struct Q : public tuple<int, uint64_t, uint64_t>{
	int sign;
	uint64_t n, d;
	Q(int64_t _n, int64_t _d):n(std::abs(_n)), d(std::abs(_d)) {
		int sn = (_n>0) - (_n<0);
		int sd = (_d>0) - (_d<0);
		sign = sn*sd;
		uint64_t g = gcd(n, d);
		n /= g;
		d /= g;
		get<0>(*this) = sign;
		get<1>(*this) = n;
		get<2>(*this) = d;
	}
};

inline int64_t det(const vector<P> &p, int i, int j, int k) {
	return 2*(p[i].x*p[j].y - p[i].x*p[k].y - p[i].y*p[j].x + p[i].y*p[k].x + p[j].x*p[k].y - p[j].y*p[k].x);
}

inline Q x(const vector<P> &p, int i, int j, int k) {
	int64_t d = det(p, i, j, k);
	return Q((p[i].x*p[i].x*p[j].y - p[i].x*p[i].x*p[k].y + p[i].y*p[i].y*p[j].y - p[i].y*p[i].y*p[k].y - p[i].y*p[j].x*p[j].x - p[i].y*p[j].y*p[j].y + p[i].y*p[k].x*p[k].x + p[i].y*p[k].y*p[k].y + p[j].x*p[j].x*p[k].y + p[j].y*p[j].y*p[k].y - p[j].y*p[k].x*p[k].x - p[j].y*p[k].y*p[k].y), d);
}

inline Q y(const vector<P> &p, int i, int j, int k) {
	int64_t d = det(p, i, j, k);
	return Q((-p[i].x*p[i].x*p[j].x + p[i].x*p[i].x*p[k].x + p[i].x*p[j].x*p[j].x + p[i].x*p[j].y*p[j].y - p[i].x*p[k].x*p[k].x - p[i].x*p[k].y*p[k].y - p[i].y*p[i].y*p[j].x + p[i].y*p[i].y*p[k].x - p[j].x*p[j].x*p[k].x + p[j].x*p[k].x*p[k].x + p[j].x*p[k].y*p[k].y - p[j].y*p[j].y*p[k].x), d);
}

inline Q r2(const vector<P> &p, int i, int j, int k) {
	int64_t d = det(p, i, j, k); // d*d will overflow ;-( but will try if it goes thru anyways ;-)
	return Q((p[i].x*p[i].x - 2*p[i].x*p[j].x + p[i].y*p[i].y - 2*p[i].y*p[j].y + p[j].x*p[j].x + p[j].y*p[j].y)*(p[i].x*p[i].x - 2*p[i].x*p[k].x + p[i].y*p[i].y - 2*p[i].y*p[k].y + p[k].x*p[k].x + p[k].y*p[k].y)*(p[j].x*p[j].x - 2*p[j].x*p[k].x + p[j].y*p[j].y - 2*p[j].y*p[k].y + p[k].x*p[k].x + p[k].y*p[k].y), d*d);
}

bool can_circle(const vector<P> &p, vector<int> s) {
	if (s.size() < 3) {
		return true;
	} else {
		Q cx(0,0), cy(0,0), cr2(0,0);
		if (det(p, s[0], s[1], s[2]) != 0) {
			cx = x(p, s[0], s[1], s[2]);
			cy = y(p, s[0], s[1], s[2]);
			cr2 = r2(p, s[0], s[1], s[2]);
		} else {
			return false;
		}
		int ns = s.size();
		for (int i=0; i<ns-2; i++)
			for (int j=i+1; j<ns-1; j++)
				for (int k=j+1; k<ns; k++)
					if (det(p, s[i], s[j], s[k]) == 0 ||
						cx != x(p, s[i], s[j], s[k]) ||
						cy != y(p, s[i], s[j], s[k]) ||
						cr2 != r2(p, s[i], s[j], s[k]))
						return false;
		return true;
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<P> pp(n);
	for (auto &p:pp)
		cin >> p.x >> p.y;
	// for 3+4 points we can always identify the exact center/radius of one circle
	int lmn = min(7, n);
	vector<int> c1, c2;
	for (int pw=0; pw < (1<<lmn); pw++) {
		vector<int> s1, s2;
		for (int i=0; i<lmn; i++)
			if (pw & (1<<i))
				s1.push_back(i);
			else
				s2.push_back(i);
		if (can_circle(pp, s1) && can_circle(pp, s2)) {
			if (s1.size() > c1.size()) {
				c1 = s1;
				c2 = s2;
			}
		}
	}
	string o1, o2;
	for (auto i:c1)
		o1 += to_string(i+1) + " ";
	for (auto i:c2)
		o2 += to_string(i+1) + " ";
	//assert(c1.size() > 2);
	c1.resize(4);
	for (int i=lmn; i<n; i++) {
		c1[3] = i;
		if (can_circle(pp, c1))
			o1 += to_string(i+1) + " ";
		else
			o2 += to_string(i+1) + " ";
	}
	if (o2 == "")
		o2 = "1";
	cout << o1 << endl;
	cout << o2 << endl;
	return 0;
}
