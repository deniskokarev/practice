/* ACMP 856 */
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

struct P {
	int64_t x, y;
	void operator+=(const P &b) {
		x += b.x;
		y += b.y;
	}
};


/*
 * I'm too old for this shit - using python sympy to solve the system
 *

# x_1 = v_x * t + c_x
# y_1 = v_y * t + c_y
# (x-x_1) * v_x + (y-y_1) * v_y = 0
# (x_1-c_x) * (y-y_1) - (y_1-c_y) * (x-x_x1) = l * sqrt((x_1-c_x)^2 + (y_1-c_y)^2)

import sympy
from sympy import Symbol, Eq, solve, sqrt

x_1 = Symbol('x_1')
y_1 = Symbol('y_1')
v_x = Symbol('v.x', constant = True)
v_y = Symbol('v.y', constant = True)
y = Symbol('y', constant = True)
x = Symbol('x')
t = Symbol('t')
c_x = Symbol('c.x', constant = True)
c_y = Symbol('c.y', constant = True)
l = Symbol('l', constant = True)

eq1 = x_1 - v_x * t - c_x
eq2 = y_1 - v_y * t - c_y
eq3 = (x-x_1) * v_x + (y-y_1) * v_y
eq4 = (x_1-c_x) * (y-y_1) - (y_1-c_y) * (x-x_1) - l * sqrt((x_1-c_x)**2 + (y_1-c_y)**2)

sol = solve([eq1, eq2, eq3, eq4], x_1, y_1, t, x, dict=True)

print sol[0][x]
print sol[1][x]

# Out:
# (c.x*v.y**2 - c.y*v.x*v.y + v.x*v.y*y - sqrt(l**2*v.y**2*(v.x**2 + v.y**2)))/v.y**2
# (c.x*v.y**2 - c.y*v.x*v.y + v.x*v.y*y + sqrt(l**2*v.y**2*(v.x**2 + v.y**2)))/v.y**2

 */

int main(int argc, char **argv) {
	int64_t r, n;
	cin >> r >> n;
	int64_t q;
	cin >> q;
	P c;
	cin >> c.x >> c.y;
	P v;
	cin >> v.x >> v.y;
	assert(v.y != 0);
	// augmented radius of the ball
	int64_t l = r+q;
	int64_t s = 0;
	for (int64_t y=0; y<n; y++) {
		int64_t xl = ceil(((c.x*v.y*v.y - c.y*v.x*v.y + v.x*v.y*y) - l*sqrt(v.y*v.y*(v.x*v.x + v.y*v.y))/1e3)/v.y/v.y);
		int64_t xr = floor(((c.x*v.y*v.y - c.y*v.x*v.y + v.x*v.y*y) + l*sqrt(v.y*v.y*(v.x*v.x + v.y*v.y))/1e3)/v.y/v.y);
		//cerr << "y: " << y << " xl: " << xl << " xr: " << xr << endl;
		xl += y;
		xr += y;
		int cr = min(xr, 2*y)/2;
		int cl = (max(xl, 0LL)+1)/2;
		s += cr-cl+1;
		//cerr << "y: " << y << " cnt: " << cr-cl+1 << endl;
	}
	cout << s << endl;
	return 0;
}
